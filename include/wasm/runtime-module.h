#include <function.h>
#include <static-module.h>

class RuntimeModule {
public:
    RuntimeModule(StaticModule *static_module) : static_module_(static_module) { load_functions(); }

    StaticModule *static_module() const { return static_module_; }
    void invoke_function(int idx, bool startFunction = false);
private:
    StaticModule *static_module_;
    std::map<int, Function> functions_;

    void load_functions();
};
