#include "ui.h"
#include "engine.h"
#include "render.h"
#include <iostream>

UI::UI(std::string name) : Module(name)
{
}

UI::~UI()
{
}

bool UI::LoadConfig(std::string config_file)
{
    font = LoadFont("../models/nulshock bd.otf");
    return true;
}

bool UI::Start()
{
    return true;
}

bool UI::Update(double delta_time)
{
    Vector3 cameraPositon = engine->render->GetCamera()->position;
    cameraString = "Position: " + std::to_string((int)cameraPositon.x) + ", " + std::to_string((int)cameraPositon.y) + ", " + std::to_string((int)cameraPositon.z);
    return true;
}

void UI::Cleanup()
{
}

void UI::DrawUi()
{
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, BLACK);
    DrawTextEx(font, cameraString.c_str(), {position.x, position.y + verticalSpacing + fontSize}, fontSize, 1, BLACK);
}

