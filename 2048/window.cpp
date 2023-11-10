#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "window.hpp"

Window::Window(std::ostream &outputStream) : outputStream(outputStream) {}

std::string Window::drawTitle() {
    std::ostringstream title;

    title << COLOR_MAGENTA;

    title << "      ___   ___  _  _   ___" << std::endl << "\r";
    title << R"(     |__ \ / _ \| || | / _ \)" << std::endl << "\r";
    title << "        ) | | | | || || (_) |" << std::endl << "\r";
    title << "       / /| | | |__   _> _ <" << std::endl << "\r";
    title << "      / /_| |_| |  | || (_) |" << std::endl << "\r";
    title << "     |____|\\___/   |_| \\___/" << std::endl << "\r";

    title << ANSI_COLOR_RESET;

    return title.str();
}

std::string Window::drawStats(size_t moves, size_t score) {
    std::stringstream stats;
    stats << COLOR_MAGENTA << ANSI_BOLD;
    stats << "SCORE: " << score << std::endl << "\r";
    stats << "MOVES: " << moves << std::endl << "\r";
    stats << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
    return stats.str();
}

std::string Window::drawBoard(size_t size) {
    std::stringstream board;

    // Draw top border
    board << "+";
    for (size_t column = 0; column < size; ++column) {
        board << "--------+";
    }
    board << std::endl << "\r";

    // Draw table content
    for (size_t row = 0; row < size; ++row) {
        for (size_t column = 0; column < size; ++column) {
            board << "|" << std::setw(7) << "123456" << " ";
        }
        board << "|" << std::endl << "\r";

        // Draw row separator
        board << "+";
        for (size_t column = 0; column < size; ++column) {
            board << "--------+";
        }
        board << std::endl << "\r";
    }


    return board.str();
}

std::string Window::drawText(bool gameOver) {
    std::stringstream text;

    if (gameOver) {
        text << "Game over ():  " << std::endl << "\r";
        text << "R => play again, Q => Quit" << std::endl << "\r";
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

void Window::renderWindow(size_t size, bool gameOver, size_t moves, size_t score) {
    std::stringstream buffer;

    buffer << ANSI_CLEAR << ANSI_COLOR_RESET;
    buffer << drawTitle() << std::endl << "\r";
    buffer << drawBoard(size) << std::endl << "\r";
    buffer << drawStats(moves, score) << std::endl << "\r";
    buffer << drawText(gameOver) << std::endl << "\r";

    outputStream << buffer.str();
}
