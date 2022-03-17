#include <string>

class Runtime {
public:
    Runtime() {}
    ~Runtime() {}

    void load_module(const std::string &path);
    void run();
};

class load_exception : public std::runtime_error
{
public:
    load_exception(const std::string &message) : runtime_error(message) {}
};