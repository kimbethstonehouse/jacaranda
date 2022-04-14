#pragma once
#include <fstream>

#define SOCKET_FILE "/tmp/jitaas"
#define BACKLOG 5
#define MAX_FILE_SIZE 102400 // 100KB max
#define BIN_FILE_NAME "test"

inline size_t align(size_t a, size_t b) { return (1 + (a - 1) / b) * b; }

///** Read file into buffer. */
inline int read(const char *path, char *buffer) {
    std::ifstream file(path);
    file.open("r");
    int i = -1;
    if (file.is_open()) {
        i = 0;
        while(!file.eof() && i < MAX_FILE_SIZE) {
            file.get(buffer[i]);
            i++;
        }
    }
    file.close();
    return i;
}