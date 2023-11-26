#ifndef INC_2048_GRAPHICS_HPP
#define INC_2048_GRAPHICS_HPP

#include <sstream>
#include <vector>

#define ANSI_CLEAR "\x1B[2J\x1B[H"  // clear terminal
#define ANSI_COLOR_RESET "\x1B[m"   // color reset
#define ANSI_BOLD "\033[1m" // bold
#define ANSI_B0LD_RESET "\033[0m" // bold reset
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_CYAN "\x1B[36m"

class Graphics {
public:
    explicit Graphics(std::ostream &outputStream);

    /**
     * @brief Renders the Game window with the current Game state and information.
     * @param board A 2D vector representing the Game board.
     * @param size The size of the Game board (number of rows/columns).
     * @param gameOver A boolean flag indicating whether the Game is over or not.
     * @param moves The number of moves made in the Game.
     * @param score The current score achieved in the Game.
     * @param minutes The number of minutes elapsed in the Game.
     * @param seconds The number of seconds elapsed in the Game.
     */
    void renderWindow(const std::vector<std::vector<size_t>>& board, size_t size, bool gameOver, size_t moves, size_t score, size_t minutes, size_t seconds);

    /**
     * @brief Prints help information for the 2048 Game program.
     */
    static void printHelpInfo();

private:
    std::ostream &outputStream;

    /**
     * @brief Generates a formatted ASCII art title for the graphics, optionally with a Game over theme.
     * @param gameOver A boolean flag indicating whether the Game is over or not.
     * @return A string containing the formatted ASCII art title.
     */
    std::string drawTitle(bool gameOver);

    /**
     * @brief Generates a formatted string representing Game statistics with ANSI escape codes for color and formatting.
     * @param moves The number of moves made in the Game.
     * @param score The current score achieved in the Game.
     * @param minutes The number of minutes elapsed in the Game.
     * @param seconds The number of seconds elapsed in the Game.
     * @return A string containing the formatted Game statistics with ANSI escape codes.
     */
    std::string drawStats(size_t moves, size_t score, size_t minutes, size_t seconds);

    /**
     * @brief Generates a formatted string representing the Game board with ANSI escape codes for color and formatting.
     * @param board A 2D vector representing the Game board.
     * @param size The size of the Game board (number of rows/columns).
     * @return A string containing the formatted Game board with ANSI escape codes.
     */
    std::string drawBoard(const std::vector<std::vector<size_t>>& board, size_t size);

    /**
     * @brief Generates a formatted string representing text instructions for the Game with ANSI escape codes for color and formatting.
     * @param gameOver A boolean flag indicating whether the Game is over or not.
     * @return A string containing the formatted text instructions with ANSI escape codes.
     */
    std::string drawText(bool gameOver);

    /**
     * @brief Converts a given number to an ANSI color code in the range 31 to 37.
     * @param number The numeric value to be converted to an ANSI color code.
     * @return A string containing the ANSI escape code for the determined color.
     */
    std::string convertToColorANSI(size_t number);
};

#endif //INC_2048_GRAPHICS_HPP
