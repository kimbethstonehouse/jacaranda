#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <wasm.h>
#include <payload.h>
#include <function.h>

// A lazily parsed WebAssembly module.
class WasmModule {
public:
    WasmModule(const std::string &filename);
    ~WasmModule();

    template <class T> T *get_section() { return (T *)section_map_[T::id]; }

    std::map<int, std::shared_ptr<WasmFunction>> &functions() { return functions_; }
    int function_count() { return function_count_; }
    int main_idx() { return main_idx_; }
    bool has_start_idx() { return start_idx_.has_value(); }
    int start_idx() { return start_idx_.value(); }

private:
    const char *buffer_, *buffer_end_;
    size_t buffer_size_;

    std::map<int, void *> section_map_;
    std::vector<void *> custom_sections_;

    std::map<int, std::shared_ptr<WasmFunction>> functions_;
    int function_count_;
    std::optional<int> start_idx_;
    int main_idx_;

    template <class T> void add_section(T *section) { section_map_[T::id] = section; }

    void parse_sections();
    void load_functions();

    template <typename T = unsigned int> T read_uleb128(const char *&p, VaruintN limit) {
        T result = 0;
        T shift = 0;
        T length = 0;

        while (true) {
            char c = *p++;

            result |= (c & 0x7f) << shift;
            shift += 7;
            length += 7;

            if (!(c & 0x80) || length >= limit) { // The limit is at most ceil(limit / 7) bytes
                break;
            }
        }

        return result;
    }
};

