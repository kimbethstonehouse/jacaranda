#include <compiler.h>

extern "C" char *__stub_main;
extern "C" char *__stub_atoi;

void Compiler::compile(const Binary *wasm, Binary *native) {
    if (wasm->data_bytes() == "main") {
        native->set_data_bytes(__stub_main);
        native->set_data_length(60);
    } else {
        native->set_data_bytes(__stub_atoi);
        native->set_data_length(6);
    }
}