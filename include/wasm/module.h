#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <wasm.h>
#include<payload.h>

class Module {
public:
    Module(const std::string &filename);
    ~Module() {}

    template <class T> T *get_section() { return (T *)section_map_[T::ID]; }

private:
    const char *buffer_, *buffer_end_;
    size_t buffer_size_;

    std::map<int, void *> section_map_;
    std::vector<void *> custom_sections_;

    template <class T> void add_section(T *section) { section_map_[T::id] = section; }

    void parse_sections();

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

