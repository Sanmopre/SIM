#include "physics.h"
#include <iostream>

Physics::Physics(std::string name) : Module(name)
{
}

Physics::~Physics()
{
}

bool Physics::LoadConfig(std::string config_file)
{
    return true;
}

bool Physics::Start()
{

    return true;
}

bool Physics::Update(double delta_time)
{
    return true;
}

void Physics::Cleanup()
{
}

