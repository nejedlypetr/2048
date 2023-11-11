#include <iostream>
#include <sstream>
#include <iomanip>

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

std::string Window::drawStats(size_t moves, size_t score, size_t minutes, size_t seconds) {
    std::stringstream stats;
    stats << COLOR_MAGENTA << ANSI_BOLD;
    stats << "SCORE: " << score << std::endl << "\r";
    stats << "MOVES: " << moves << std::endl << "\r";
    stats << "TIME: " << std::setw(2) << std::setfill('0') << minutes << ":";
    stats << std::setw(2) << std::setfill('0') << seconds << "s" << std::endl << "\r";
    stats << ANSI_COLOR_RESET << ANSI_B0LD_RESET;
    return stats.str();
}

std::string Window::drawBoard(const std::vector<std::vector<size_t>>& board, size_t size) {
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
            if (board[row][column] != 0) {
                number = std::to_string(board[row][column]);
            }
            output << "|" << std::setw(7) << number << " ";
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

void Window::renderWindow(const std::vector<std::vector<size_t>>& board, size_t size, bool gameOver, size_t moves, size_t score, size_t minutes, size_t seconds) {
    std::stringstream buffer;

    buffer << ANSI_CLEAR << ANSI_COLOR_RESET;
    buffer << drawTitle() << std::endl << "\r";
    buffer << drawBoard(board, size) << std::endl << "\r";
    buffer << drawStats(moves, score, minutes, seconds) << std::endl << "\r";
    buffer << drawText(gameOver) << std::endl << "\r";

    outputStream << buffer.str();
}
