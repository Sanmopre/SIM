#include "render.h"
#include <iostream>

Render::Render(std::string name) : Module(name) {

}

Render::~Render() {

}

bool Render::LoadConfig(std::string config_file) 
{
    return true;
}

bool Render::Start() 
{
// create a simple 3d camera that moves with the arrow keys and rotates with the mouse
camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
camera.fovy = 45.0f;                                // Camera field-of-view Y
camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);

    model = LoadModel("models/sirtap.obj");        

    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture); 

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
    ClearBackground(RAYWHITE);
    
        BeginMode3D(camera);
        DrawTriangle3D(Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 10.0f, 10.0f }, Vector3{ 0.0f, 0.0f, 10.0f }, Color{ 255, 0, 0, 255 });   
        DrawModelEx(model, Vector3{ 0.0f, 0.0f, 0.0f }, Vector3{ 1.0f, 0.0f, 0.0f }, 0.0f, Vector3{ 0.20f, 0.20f, 0.20f }, WHITE);
        DrawGrid(10, 1.0f);

        EndMode3D();
    EndDrawing();

    return true;
}

void Render::Cleanup() 
{
    CloseWindow();
}
