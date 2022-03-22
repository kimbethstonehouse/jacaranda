#include <compiler.h>

int main() {
    Compiler compiler;
    compiler.open_socket();
    compiler.handle_connections();
}