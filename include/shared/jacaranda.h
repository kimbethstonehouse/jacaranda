#pragma once

#include <fstream>

#define MAX_FILE_SIZE 102400 // 100KB max
#define PTR_SIZE 8

static const std::string compiler_address("0.0.0.0:50051");
static const std::string runtime_address("0.0.0.0:50052");
static const std::string repository_address("0.0.0.0:50053");

inline size_t align(size_t a, size_t b) { return (1 + (a - 1) / b) * b; }

///** Read file into buffer. */
inline int read(const char *path, char *buffer) {
    std::ifstream file(path);
    file.open(path, std::ifstream ::binary);
    int i = -1;
    if (file.is_open()) {
        i = 0;
        while(!file.eof() && i < MAX_FILE_SIZE) {
            char c;
            file.get(c);
            i++;
        }
    }
    file.close();
    return i;
}