#pragma once

#include <iostream>
#include <cstring>

#define print_to_file(fmt, ...) { \
    auto pFile = fopen("parsers.log", "a"); \
    if (pFile) { \
        std::fprintf(pFile, fmt, ##__VA_ARGS__); \
    } \
    fclose(pFile); \
}

#define log_inf(fmt, ...) { \
    std::printf(fmt, ##__VA_ARGS__); \
    print_to_file(fmt, ##__VA_ARGS__); \
}

#define log_err(fmt, ...) { \
    std::printf(fmt, ##__VA_ARGS__); \
    print_to_file(fmt, ##__VA_ARGS__); \
}

#define log_dbg(fmt, ...) { \
    print_to_file(fmt, ##__VA_ARGS__); \
}
