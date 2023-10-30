#include <string>
#include <vector>
#include "module.h"
#include "render.h"

class Engine {
public:
    Engine();
    ~Engine();
    bool LoadConfig(std::string config_file);
    bool Start();
    bool Update();
    void Cleanup();

    Render* render = nullptr;

private:

    double delta_time = 0.0;
    std::vector<Module*> modules;

};
