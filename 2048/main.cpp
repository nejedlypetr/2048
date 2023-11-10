#include <iostream>
#include <chrono>
#include <thread>

#include "argumentsparser.hpp"
#include "window.hpp"

#define KEY_UP 'A'
#define KEY_LEFT 'D'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

class game_2048 {
public:
    explicit game_2048(size_t size) : size(size), window(std::make_unique<Window>(std::cout)) {
        window->renderWindow(size, gameOver, moves, score, minutes, seconds);
    };

    void input() {
        std::unique_lock<std::mutex> lock(mutex);
        lock.unlock();

        char c;
        std::cin >> c;

        if (c == 'q' || c == 'Q') {
            quit = true;
            cv.notify_one();
            return;
        } else if (c == 'w' || c == 'W' || c == KEY_UP) {
            direction = UP;
        } else if (c == 's' || c == 'S' || c == KEY_DOWN) {
            direction = DOWN;
        } else if (c == 'a' || c == 'A' || c == KEY_LEFT) {
            direction = LEFT;
        } else if (c == 'd' || c == 'D' || c == KEY_RIGHT) {
            direction = RIGHT;
        } else {
            direction = NONE;
            return;
        }
        game_mechanics(direction);

        cv.notify_one();
    }

    void game_mechanics(Direction direction) {
        moves += 1;

    }

    void output() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);

        window->renderWindow(size, gameOver, moves, score, minutes, seconds);
    }

    void calculate() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::unique_lock<std::mutex> lock(mutex);

        ++seconds;
        if (seconds == 60) {
            seconds = 0;
            minutes += 1;
        }

        cv.notify_all();
    }

    bool get_quit() const {
        return quit;
    }

private:
    bool quit = false;
    bool gameOver = false;
    Direction direction = NONE;
    size_t size;
    size_t score = 0;   // current game score
    size_t moves = 0;   // total number of moves
    std::mutex mutex;
    std::condition_variable cv;
    std::unique_ptr<Window> window;
    size_t seconds = 0;
    size_t minutes = 0;
};

int main(int argc, char *argv[]) {
    auto inputThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.input();
        }
    };

    auto computeThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.calculate();
        }
    };

    auto outputThread = [](game_2048& game) {
        while (!game.get_quit()) {
            game.output();
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
