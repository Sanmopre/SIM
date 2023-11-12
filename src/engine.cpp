#include "engine.h"
#include <iostream>
#include "globals.h"

Engine::Engine()
{
    render = new Render("render");
    mapGenerator = new MapGenerator("mapGenerator");

    modules.push_back(mapGenerator);
    modules.push_back(render);
}

Engine::~Engine()
{

}

bool Engine::LoadConfig(std::string config_file)
{
    
    for (auto mod : modules)
    {
        if(!mod->LoadConfig(mod->name + "_config.xml"))
        {
            std::cout << "Module " << mod->name << " failed to load config." << "\n";
            return false;
        }
    }
    return true;
}

bool Engine::Start()
{
    for(auto mod : modules)
    {
        if(!mod->Start())
        {
            std::cout << "Module " << mod->name << " failed to start." << "\n";
            return false;
        }
    }

    return true;
}

bool Engine::Update()
{
    Timer timer;
    for(auto mod : modules)
    {  
        if(!mod->Update(delta_time))
        {
            std::cout << "Module " << mod->name << " failed to update." << "\n";
            return false;
        }
    }
    delta_time = timer.elapsed();

    return true;
}

void Engine::Cleanup()
{
    for(auto mod : modules)
    {
        mod->Cleanup();
    }

}