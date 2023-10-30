#include "engine.h"
#include "globals.h"

int main(void)
{
    Engine engine = Engine();
    engine.LoadConfig("config.xml");   
    engine.Start();

    bool running = true;
    while(running)
    {
        running = engine.Update();
    }
    
    engine.Cleanup();
    return 0;
}
