#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include "module.h"
#include "render.h"
#include "mapGenerator.h"

class Engine {
public:
    Engine();
    ~Engine();
    bool LoadConfig(std::string config_file);
    bool Start();
    bool Update();
    void Cleanup();

    Render* render = nullptr;
    MapGenerator* mapGenerator = nullptr;



private:

    double delta_time = 0.0;
    std::vector<Module*> modules;

};

extern Engine* engine;

#endif // ENGINE_H
