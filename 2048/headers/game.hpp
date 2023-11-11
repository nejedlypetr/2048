#ifndef INC_2048_GAME_HCC
#define INC_2048_GAME_HCC

#include "graphics.hpp"

#include <chrono>
#include <thread>

#define KEY_UP 'A'
#define KEY_LEFT 'D'
#define KEY_RIGHT 'C'
#define KEY_DOWN 'B'

enum Direction { UP, DOWN, LEFT, RIGHT };

class game {
public:
    explicit game(size_t size);

    void input();
    void output();
    void calculate();
    bool get_quit() const;

private:
    bool quit = false;
    bool gameOver = false;
    Direction direction = UP;
    size_t score = 0;   // current game score
    size_t moves = 0;   // total number of moves
    size_t seconds = 0;
    size_t minutes = 0;
    size_t size; // board size - number of rows and columns
    std::vector<std::vector<size_t>> board;
    std::unique_ptr<Graphics> window;
    std::mutex mutex;
    std::condition_variable cv;

    void game_mechanics();
    void move();
    void moveLeft();
    void moveRight();
    void transposeBoard();
    void moveUp();
    void moveDown();
    bool isGameOver();
    void newGame();
    void generate_number();
    size_t random(size_t bottomLimit, size_t upperLimit);
};

#endif //INC_2048_GAME_HCC
