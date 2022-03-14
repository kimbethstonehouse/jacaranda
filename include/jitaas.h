#include <fstream>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5
#define MAX_FILE_SIZE 102400 // 100KB max
#define BIN_FILE_NAME "a.out"

///** Read file into buffer. */
//inline int read(const char *path, char *buffer) {
//    std::ifstream file(path);
//    int i = -1;
//    if (file.is_open()) {
//        i = 0;
//        while(!file.eof() && i < MAX_FILE_SIZE) {
//            file.get(buffer[i]);
//            i++;
//        }
//    }
//    file.close();
//    return i;
//}