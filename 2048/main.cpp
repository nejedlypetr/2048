#include <iostream>
#include <chrono>
#include <thread>
#include <random>

#include "argumentsparser.hpp"
#include "window.hpp"

#define KEY_UP 'A'
#define KEY_LEFT 'D'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

enum Direction { UP, DOWN, LEFT, RIGHT };

class game_2048 {
public:
    explicit game_2048(size_t size) : size(size), board(size, std::vector<size_t>(size, 0)), window(std::make_unique<Window>(std::cout)) {
        generate_number();
        generate_number();
        window->renderWindow(board, size, gameOver, moves, score, minutes, seconds);
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
        }

        if (gameOver) {
            return;
        }

        if (c == 'w' || c == 'W' || c == KEY_UP) {
            direction = UP;
        } else if (c == 's' || c == 'S' || c == KEY_DOWN) {
            direction = DOWN;
        } else if (c == 'a' || c == 'A' || c == KEY_LEFT) {
            direction = LEFT;
        } else if (c == 'd' || c == 'D' || c == KEY_RIGHT) {
            direction = RIGHT;
        } else {
            return;
        }
        game_mechanics();
        cv.notify_one();
    }

    void output() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);

        window->renderWindow(board, size, gameOver, moves, score, minutes, seconds);
    }

    void calculate() {
        if (gameOver) {
            return;
        }

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
    Direction direction = UP;
    size_t size; // board size - number of rows and columns
    std::vector<std::vector<size_t>> board;
    size_t score = 0;   // current game score
    size_t moves = 0;   // total number of moves
    std::mutex mutex;
    std::condition_variable cv;
    std::unique_ptr<Window> window;
    size_t seconds = 0;
    size_t minutes = 0;

    void game_mechanics() {
        move();
        generate_number();
    }

    void move() {
        switch (direction) {
            case UP: {
                moveUp();
                break;
            }
            case DOWN: {
                moveDown();
                break;
            }
            case RIGHT: {
                moveRight();
                break;
            }
            case LEFT: {
                moveLeft();
                break;
            }
        }
    }

    void moveLeft() {
        for (size_t row = 0; row < size; row++) {
            // Remove zeros
            board[row].erase(
                    std::remove(board[row].begin(), board[row].end(), 0),
                    board[row].end()
            );

            // Merge equal values
            if (board[row].size() > 1) {
                for (size_t col = 0; col < board[row].size() - 1; col++) {
                    if (board[row][col] == board[row][(col + 1)]) {
                        board[row][col] *= 2;
                        board[row][col + 1] = 0;
                        col++;
                    }
                }

                // Remove zeros again
                board[row].erase(
                        std::remove(board[row].begin(), board[row].end(), 0),
                        board[row].end()
                );
            }

            // Add zeros to the end to match the original size
            size_t zerosToAdd = size - board[row].size();
            board[row].insert(board[row].end(), zerosToAdd, 0);
        }
    }

    void moveRight() {
        for (size_t row = 0; row < size; row++) {
            std::reverse(board[row].begin(), board[row].end());
        }
        moveLeft();
        for (size_t row = 0; row < size; row++) {
            std::reverse(board[row].begin(), board[row].end());
        }
    }

    void transposeBoard() {
        size_t boardSize = board.size();
        std::vector<std::vector<size_t>> transposedBoard(boardSize, std::vector<size_t>(boardSize, 0));

        // Transpose the board
        for (size_t row = 0; row < boardSize; ++row) {
            for (size_t col = 0; col < boardSize; ++col) {
                transposedBoard[col][row] = board[row][col];
            }
        }

        board = transposedBoard;
    }

    void moveUp() {
        transposeBoard();
        moveLeft();
        transposeBoard();
    }

    void moveDown() {
        transposeBoard();
        moveRight();
        transposeBoard();
    }

    bool isGameOver() {
        for (size_t row = 0; row < board.size(); row++) {
            for (size_t col = 0; col < board[row].size() - 1; col++) {
                if (board[row][col] == board[row][col + 1]) {
                    return false;
                }
            }
        }
        for (size_t row = 0; row < board.size(); row++) {
            for (size_t col = 0; col < board[row].size() - 1; col++) {
                if (board[col][row] == board[col +1][row]) {
                    return false;
                }
            }
        }
        return true;
    }

    void generate_number() {
        std::vector<std::pair<size_t, size_t>> emptyCells;

        for (size_t r = 0; r < size; ++r) {
            for (size_t c = 0; c < size; ++c) {
                if (board[r][c] == 0) {
                    std::pair<size_t, size_t> cell(r, c);
                    emptyCells.push_back(cell);
                }
            }
        }

        if (emptyCells.empty()) {
            gameOver = isGameOver();
            return;
        }

        moves += 1;

        std::pair<size_t, size_t> selectedCell = emptyCells[random(0, emptyCells.size()-1)];
        size_t value = (random(1, 3) == 1) ? 4 : 2;

        board[selectedCell.first][selectedCell.second] = value;
    }

    size_t random(size_t bottomLimit, size_t upperLimit) {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<size_t> distribution(bottomLimit, upperLimit);
        return distribution(generator);
    }

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
