#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

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

    template <typename T = unsigned int> T read_uleb128(const char *&p)
    {
        T result = 0;
        T shift = 0;

        while (true) {
            char c = *p++;

            result |= (c & 0x7f) << shift;
            if (!(c & 0x80)) {
                break;
            }

            shift += 7;
        }

        return result;
    }
};

class load_exception : public std::runtime_error
{
public:
    load_exception(const std::string &message) : runtime_error(message) {}
};

