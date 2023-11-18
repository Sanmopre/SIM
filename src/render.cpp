#include "render.h"
#include "engine.h"
#include "ui.h"
#include <iostream>

Render::Render(std::string name) : Module(name) 
{
    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);
}

Render::~Render() {

}

bool Render::LoadConfig(std::string config_file) 
{
    return true;
}

bool Render::Start() 
{
    camera.position = Vector3{ 0.0f, 200.0f, 1.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    return true;
}

bool Render::Update(double delta_time) 
{
    if(IsKeyDown(KEY_ESCAPE)) 
        return false;

    if(IsKeyDown(KEY_LEFT_SHIFT)) 
        camera.position.y -= 0.2f;

    if(IsKeyDown(KEY_SPACE)) 
        camera.position.y += 0.2f;


    DisableCursor();
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);

    BeginDrawing();
    ClearBackground(Color{ 204, 229, 255, 255 });
        
        BeginMode3D(camera);
        engine->mapGenerator->DrawMap();
        EndMode3D();
        engine->ui->DrawUi();
    EndDrawing();

    return true;
}

void Render::Cleanup() 
{
    CloseWindow();
}


