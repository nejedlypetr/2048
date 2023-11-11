#include "headers/argumentsparser.hpp"

#include <string>

void set_raw(bool set) {
    if (set) system("stty raw");
    else system("stty -raw");
}

Arguments ArgumentsParser::parseArguments(int argc, char **argv) {
    auto parsedArguments = Arguments{ARG_SIZE_DEFAULT};

    for (int i = 1; i < argc; i += 2) {
        int tmp;
        if (std::strlen(argv[i]) > 1)
            switch (argv[i][1]) {
                case 's':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-size")) &&
                        strToInt(&tmp, argv[i + 1]) >= 0 && tmp >= ARG_SIZE_MIN && tmp <= ARG_SIZE_MAX)
                        parsedArguments.size = tmp;
                    break;
                default:
                    break;
            }
    }

    return parsedArguments;
}

int ArgumentsParser::strToInt(int *res, const char *str) {
    try {
        *res = std::stoi(str);
    } catch (const std::invalid_argument &e) {
        return -1;
    } catch (const std::out_of_range &e) {
        return -2;
    }
    return 0;
}
