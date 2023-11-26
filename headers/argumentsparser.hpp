#ifndef INC_2048_ARGUMENTSPARSER_HPP
#define INC_2048_ARGUMENTSPARSER_HPP

#define ARG_SIZE_DEFAULT 4
#define ARG_SIZE_MIN 3
#define ARG_SIZE_MAX 5

struct Arguments {
    int size;
    bool helpRequested;
};

class ArgumentsParser {
public:
    /**
     * @brief Parses command-line arguments and extracts relevant information.
     * @param argc The number of command-line arguments.
     * @param argv An array of C-style strings representing the command-line arguments.
     * @return An instance of the Arguments struct containing parsed information.
     */
    static Arguments parseArguments(int argc, char *argv[]);

private:
    /**
     * @brief Converts a C-style string to an integer, handling potential exceptions.
     * @param res A pointer to an integer where the result will be stored.
     * @param str A C-style string to be converted to an integer.
     * @return 0 on successful conversion, -1 on invalid argument, and -2 on out-of-range.
     */
    static int strToInt(int *res, const char *str);
};

/**
 * @brief Sets or resets the terminal to raw mode for character input.
 * @param set A boolean indicating whether to set (true) or reset (false) raw mode.
 */
void set_raw(bool set);

#endif //INC_2048_ARGUMENTSPARSER_HPP
