#include <compiler.h>
#include <cstring>

extern "C" char __stub_main;
extern "C" char __stub_atoi;

std::vector<unsigned char> Compiler::compile(Payload source) {
    std::vector<unsigned char> binary;
//    if (strcmp(source.data_start(), "main")) {
//        binary.insert(binary.end(), __stub_main, __stub_main+sizeof(__stub_main));
//    } else {
//        binary.insert(binary.end(), __stub_atoi, __stub_atoi+sizeof(__stub_atoi));
//    }
    binary.push_back(0xC3);
    return binary;
}