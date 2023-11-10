#include <iostream>
#include <chrono>
#include <thread>

#include "argumentsparser.hpp"
#include "window.hpp"

#define PERIOD_COUNTER 300

class game_2048 {
public:
    explicit game_2048(size_t size) : size(size), window(std::make_unique<Window>(std::cout)) {
        window->renderWindow(size, gameOver, moves, score);
    };

    void input() {
        std::unique_lock<std::mutex> lg(mutex);
        lg.unlock();

        char c;
        std::cin >> c;

        if (c == 'q' || c == 'Q') {
            lg.lock();
            quit = true;
            cvar.notify_all();
        }
    }

    void output_area() {
        std::unique_lock<std::mutex> lg(mutex);
        cvar.wait(lg);
        if (!get_quit()) {
            window->renderWindow(size, gameOver, moves, score);
        }
    }

    void take() {
        std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_COUNTER));
        std::unique_lock<std::mutex> lg(mutex);
        ++counter;
        cvar.notify_one();
    }

    bool get_quit() const {
        return quit;
    }

private:
    bool quit = false;
    bool gameOver = false;
    int counter = 0;
    size_t size;
    size_t score = 0;   // current game score
    size_t moves = 0;   // total number of moves
    std::mutex mutex;
    std:: condition_variable cvar;
    std::unique_ptr<Window> window;
};

int main(int argc, char *argv[]) {
    auto inputThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.input();
        }
    };
    auto computeThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.take();
        }
    };
    auto outputThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.output_area();
        }
    };

    set_raw(true);

    auto arguments = ArgumentsParser::parseArguments(argc, argv);
    game_2048 game(arguments.size);

    std::thread t1(inputThread, std::ref(game));
    std::thread t2(computeThread, std::ref(game));
    std::thread t3(outputThread, std::ref(game));

    t1.join();
    t2.join();
    t3.join();

    set_raw(false);

    return 0;
}
