#ifndef MODULE_H
#define MODULE_H

#include <string>

class Module {
public:
    Module(std::string name) : name(name) {}
    virtual ~Module() {}
    virtual bool LoadConfig(std::string config_file) = 0;
    virtual bool Start() = 0;
    virtual bool Update(double delta_time) = 0;
    virtual void Cleanup() = 0;

    std::string name;
};

#endif // MODULE_H