#ifndef INC_2048_ARGUMENTSPARSER_HPP
#define INC_2048_ARGUMENTSPARSER_HPP

#define ARG_SIZE_DEFAULT 4
#define ARG_SIZE_MIN 3
#define ARG_SIZE_MAX 5

/*
 * Structure of program arguments
 */
struct Arguments {
    int size;
};

class ArgumentsParser {
public:
    /*
     *  -s (-size) - number of rows and columns
     */
    static Arguments parseArguments(int argc, char *argv[]);

private:
    /*
     * Convert string to integer
     */
    static int strToInt(int *res, const char *str);
};

/*
 * Set terminal to raw mode
 */
void set_raw(bool set);

#endif //INC_2048_ARGUMENTSPARSER_HPP
