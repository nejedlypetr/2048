#include "headers/argumentsparser.hpp"
#include "headers/game.hpp"

#include <chrono>
#include <thread>

#ifndef UNIT_TESTING
int main(int argc, char *argv[]) {
    auto arguments = ArgumentsParser::parseArguments(argc, argv);

    if (arguments.helpRequested) {
        Graphics::printHelpInfo();
        return 0;
    }

    auto inputThread = [](Game& game) {
        while (!game.get_quit()) {
            game.input();
        }
    };

    auto computeThread = [](Game& game) {
        while (!game.get_quit()) {
            game.calculate();
        }
    };

    auto outputThread = [](Game& game) {
        while (!game.get_quit()) {
            game.output();
        }
    };

    set_raw(true);

    Game game(arguments.size);

    std::thread t1(inputThread, std::ref(game));
    std::thread t2(computeThread, std::ref(game));
    std::thread t3(outputThread, std::ref(game));

    t1.join();
    t2.join();
    t3.join();

    set_raw(false);

    return 0;
}

#endif