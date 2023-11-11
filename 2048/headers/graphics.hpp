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

    /*
     * Redraw entire terminal window
     */
    void renderWindow(const std::vector<std::vector<size_t>>& board, size_t size, bool gameOver, size_t moves, size_t score, size_t minutes, size_t seconds);

private:
    std::ostream &outputStream;

    std::string drawTitle(bool gameOver);
    std::string drawStats(size_t moves, size_t score, size_t minutes, size_t seconds);
    std::string drawBoard(const std::vector<std::vector<size_t>>& board, size_t size);
    std::string drawText(bool gameOver);

    std::string convertToColorANSI(size_t number);
};

#endif //INC_2048_GRAPHICS_HPP