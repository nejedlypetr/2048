#include "headers/argumentsparser.hpp"
#include "headers/game.hpp"

#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    auto inputThread = [](game& game) {
        while (!game.get_quit()) {
            game.input();
        }
    };

    auto computeThread = [](game& game) {
        while (!game.get_quit()) {
            game.calculate();
        }
    };

    auto outputThread = [](game& game) {
        while (!game.get_quit()) {
            game.output();
        }
    };

    set_raw(true);

    auto arguments = ArgumentsParser::parseArguments(argc, argv);
    game game(arguments.size);

    std::thread t1(inputThread, std::ref(game));
    std::thread t2(computeThread, std::ref(game));
    std::thread t3(outputThread, std::ref(game));

    t1.join();
    t2.join();
    t3.join();

    set_raw(false);

    return 0;
}
