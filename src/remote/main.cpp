#include "compiler.h"

int main(int argc, char **argv) {
    Compiler compiler;

    compiler.open_socket();
    compiler.handle_connections();
}