#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include "module.h"
#include "globals.h"
#include "render.h"
#include "ui.h"
#include "mapGenerator.h"
#include "physics.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

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
    UI* ui = nullptr;
    Physics* physics = nullptr;



private:

    double delta_time = 0.0;
    std::vector<Module*> modules;

};

extern Engine* engine;

#endif // ENGINE_H
