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

class Game {
public:
    explicit Game(size_t size);
    explicit Game(const std::vector<std::vector<size_t>>& board);

    /**
     * @brief Handles user input for the Game.
     *
     * This method captures user input from the console and processes it based on the Game state.
     * It checks for various key inputs, such as arrow keys and specific characters, to perform
     * actions like quitting the Game, starting a new Game, or changing the direction of the Game.
     * The method uses a mutex to ensure thread safety for shared variables like 'quit' and 'direction'.
     * After processing the input, it notifies the waiting thread using a condition variable.
     */
    void input();

    /**
     * @brief Renders the Game window based on the current Game state.
     *
     * This method acquires a lock on the mutex and then waits on a condition variable,
     * ensuring synchronization with the `input` method. Once notified, it releases the lock
     * and calls the `renderWindow` method on the associated window object, displaying the
     * updated Game state, including the board, Game over status, moves, score, minutes, and seconds.
     */
    void output();

    /**
     * @brief Calculates and updates Game time.
     *
     * This method increments the Game timer by one second, simulating the passage of time.
     * If the timer reaches 60 seconds, it resets to 0 and increments the minutes counter.
     * The method is protected by a mutex to ensure thread safety when updating shared variables,
     * and it notifies all waiting threads using a condition variable after the calculation.
     * If the Game is over, the method returns without performing any calculations.
     */
    void calculate();

    /**
     * @brief Retrieves the current value of the 'quit' flag.
     * @return A boolean value representing the state of the 'quit' flag.
     */
    bool get_quit() const;

private:
    bool quit = false;
    bool gameOver = false;
    Direction direction = UP;
    size_t score = 0;   // current Game score
    size_t moves = 0;   // total number of moves
    size_t seconds = 0;
    size_t minutes = 0;
    // board size - number of rows and columns
    std::unique_ptr<Graphics> window;
    std::mutex mutex;
    std::condition_variable cv;

    /**
     * @brief Executes the core Game mechanics, including player movement and number generation.
     *
     * This method encapsulates the fundamental Game mechanics, comprising the player's move
     * and the generation of a new number on the Game board. It serves as a higher-level function
     * to coordinate these essential actions during the progression of the Game.
     */
    void game_mechanics();

    /**
     * @brief Executes the player's move in the direction specified by the 'direction' variable.
     *
     * This method dispatches the player's move based on the current direction. It serves as a
     * high-level interface to invoke specific movement functions (e.g., moveUp, moveDown) based
     * on the direction set by user input or Game logic. The actual movement logic is implemented
     * in the corresponding directional functions.
     */
    void move();

    /**
     * @brief Transposes the Game board, swapping rows and columns.
     *
     * This method transposes the Game board by swapping rows and columns, effectively
     * interchanging the positions of elements. It creates a new transposed board and assigns
     * it to the original board.
     */
    void transposeBoard();

    /**
     * @brief Checks if the Game is over by examining the current state of the Game board.
     *
     * This method evaluates the Game board to determine if any valid moves are available.
     * It iterates through each row and column, checking for adjacent equal values. If any
     * such equal values are found either horizontally or vertically, the Game is not over.
     * If no equal values are found in any row or column, the Game is considered over.
     *
     * @return A boolean indicating whether the Game is over (true) or not (false).
     */
    bool isGameOver();

    /**
     * @brief Starts a new Game, resetting Game state and initializing a new Game board.
     *
     * This method initializes a new Game by resetting various Game state variables, including
     * the Game over status, score, timer, and number of moves. It creates a new Game board with
     * all elements set to zero and generates two initial numbers on the board to kickstart the Game.
     */
    void newGame();

    /**
     * @brief Generates a new number on the Game board at an empty cell.
     *
     * This method identifies all empty cells on the Game board, and if any are available,
     * it randomly selects one and generates a new number (either 2 or 4) at that cell.
     * The method also updates the Game state, including the number of moves and the score.
     * If no empty cells are available, it checks if the Game is over.
     */
    void generate_number();

    /**
     * @brief Generates a random number within the specified range.
     * @param bottomLimit The lower limit of the desired range.
     * @param upperLimit The upper limit of the desired range.
     * @return A randomly generated number within the specified range.
     */
    size_t random(size_t bottomLimit, size_t upperLimit);

protected:
/**
 * @brief Executes the rightward movement logic for the Game board.
 *
 * This method implements the rightward movement logic for the Game board by reversing
 * each row, performing a leftward movement, and then reversing the rows back to their
 * original order. The reversal ensures that the logic is consistent with the movement
 * direction, achieving the desired effect of moving tiles to the right.
 */
void moveRight();

/**
 * @brief Executes the upward movement logic for the Game board.
 *
 * This method implements the upward movement logic for the Game board by transposing
 * the board, performing a leftward movement, and then transposing the board back to its
 * original orientation. The transposition allows the movement logic to be consistent with
 * the desired effect of moving tiles upwards.
 */
void moveUp();

/**
 * @brief Executes the leftward movement logic for the Game board.
 *
 * This method implements the leftward movement logic for the Game board. It removes
 * zeros, merges equal adjacent values, removes zeros again, and adds zeros to the end
 * to match the original row size. The method modifies the Game board in-place based on
 * the rules of the 2048 Game when moving tiles to the left.
 */
void moveLeft();

/**
 * @brief Executes the downward movement logic for the Game board.
 *
 * This method implements the downward movement logic for the Game board by transposing
 * the board, performing a rightward movement, and then transposing the board back to its
 * original orientation. The transposition allows the movement logic to be consistent with
 * the desired effect of moving tiles downwards.
 */
void moveDown();

    std::vector<std::vector<size_t>> board;
    size_t size;
};

#endif //INC_2048_GAME_HCC
