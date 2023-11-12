#include "engine.h"
#include "globals.h"

Engine* engine = nullptr;

int main(void)
{
    engine = new Engine();
    engine->LoadConfig("config.xml");   
    engine->Start();

    bool running = true;
    while(running)
    {
        running = engine->Update();
    }
    
    engine->Cleanup();
    return 0;
}
