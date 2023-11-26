#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "headers/graphics.hpp"
#include "headers/argumentsparser.hpp"

Graphics::Graphics(std::ostream &outputStream) : outputStream(outputStream) {}

std::string Graphics::convertToColorANSI(size_t number) {
    size_t exponent = static_cast<int>(log2(number));
    size_t colorCode = exponent % 7 + 31; // Map exponent to ANSI color codes (31 to 37)
    return "\x1B[" + std::to_string(colorCode) + "m";
}

std::string Graphics::drawTitle(bool gameOver) {
    std::ostringstream title;

    if (gameOver) {
        title << COLOR_CYAN;
        title << "   _____          __  __ ______    ______      ________ _____  " << std::endl << "\r";
        title << R"(  / ____|   /\   |  \/  |  ____|  / __ \ \    / /  ____|  __ \ )" << std::endl << "\r";
        title << R"( | |  __   /  \  | \  / | |__    | |  | \ \  / /| |__  | |__) |)" << std::endl << "\r";
        title << R"( | | |_ | / /\ \ | |\/| |  __|   | |  | |\ \/ / |  __| |  _  / )" << std::endl << "\r";
        title << R"( | |__| |/ ____ \| |  | | |____  | |__| | \  /  | |____| | \ \ )" << std::endl << "\r";
        title << R"(  \_____/_/    \_\_|  |_|______|  \____/   \/   |______|_|  \_\)" << std::endl << "\r";
        title << ANSI_COLOR_RESET;
        return title.str();
    }

    title << COLOR_CYAN;
    title << "      ___   ___  _  _   ___" << std::endl << "\r";
    title << R"(     |__ \ / _ \| || | / _ \)" << std::endl << "\r";
    title << "        ) | | | | || || (_) |" << std::endl << "\r";
    title << "       / /| | | |__   _> _ <" << std::endl << "\r";
    title << "      / /_| |_| |  | || (_) |" << std::endl << "\r";
    title << "     |____|\\___/   |_| \\___/" << std::endl << "\r";
    title << ANSI_COLOR_RESET;

    return title.str();
}

std::string Graphics::drawStats(size_t moves, size_t score, size_t minutes, size_t seconds) {
    std::stringstream stats;
    stats << COLOR_YELLOW << ANSI_BOLD;
    stats << "SCORE: " << score << std::endl << "\r";
    stats << "MOVES: " << moves << std::endl << "\r";
    stats << "TIME: " << std::setw(2) << std::setfill('0') << minutes << ":";
    stats << std::setw(2) << std::setfill('0') << seconds << "s" << std::endl << "\r";
    stats << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
    return stats.str();
}

std::string Graphics::drawBoard(const std::vector<std::vector<size_t>>& board, size_t size) {
    std::stringstream output;

    // Draw top border
    output << "+";
    for (size_t column = 0; column < size; ++column) {
        output << "--------+";
    }
    output << std::endl << "\r";

    // Draw table content
    for (size_t row = 0; row < size; ++row) {
        for (size_t column = 0; column < size; ++column) {
            std::string number;
            std::string color = ANSI_COLOR_RESET;
            if (board[row][column] != 0) {
                number = std::to_string(board[row][column]);
                color = convertToColorANSI(board[row][column]);
            }
            output << "|" << color << ANSI_BOLD << std::setw(7) << number << " " << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
        }
        output << "|" << std::endl << "\r";

        // Draw row separator
        output << "+";
        for (size_t column = 0; column < size; ++column) {
            output << "--------+";
        }
        output << std::endl << "\r";
    }


    return output.str();
}

std::string Graphics::drawText(bool gameOver) {
    std::stringstream text;

    if (gameOver) {
        text << COLOR_CYAN << ANSI_BOLD;
        text << "R => Play again, Q => Quit" << std::endl << "\r";
        text << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
    } else {
        text << COLOR_CYAN << ANSI_BOLD;
        text << "↑ or W => Up" << std::endl << "\r";
        text << "↓ or S => Down" << std::endl << "\r";
        text << "← or A => Left" << std::endl << "\r";
        text << "→ or D => Right" << std::endl << std::endl << "\r";
        text << "Q => Quit" << std::endl << "\r";
        text << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
    }

    return text.str();
}

void Graphics::renderWindow(const std::vector<std::vector<size_t>>& board, size_t size, bool gameOver, size_t moves, size_t score, size_t minutes, size_t seconds) {
    std::stringstream buffer;

    buffer << ANSI_CLEAR << ANSI_COLOR_RESET;
    buffer << drawTitle(gameOver) << std::endl << "\r";
    buffer << drawBoard(board, size) << std::endl << "\r";
    buffer << drawStats(moves, score, minutes, seconds) << std::endl << "\r";
    buffer << drawText(gameOver) << std::endl << "\r";

    outputStream << buffer.str();
}

void Graphics::printHelpInfo() {
    std::cout << "Usage: 2048 [--size <size>] [--help]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --size <size>  Set the size parameter for the program (default: " << ARG_SIZE_DEFAULT << ", min: " << ARG_SIZE_MIN << ", max: " << ARG_SIZE_MAX << ")." << std::endl;
    std::cout << "  --help         Display this help information." << std::endl;
}
