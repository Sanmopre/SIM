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
    camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);

    model = LoadModel("models/cottage_obj.obj");                    // Load the animated model mesh and basic data
    texture = LoadTexture("models/cottage_textures/cottage_diffuse.png");  
    texture2 = LoadTexture("models/cottage_textures/cottage_normal.png");        // Load model texture and set material
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture); 
    SetMaterialTexture(&model.materials[1], MATERIAL_MAP_NORMAL, texture2); 
    return true;
}

bool Render::Update(double delta_time) 
{
    if(IsKeyDown(KEY_ESCAPE))
        return false;



    angle.y = 0.0f;
    angle.x = 0.0f;

    if(IsKeyDown(KEY_UP)) 
        angle.y = -rotationSpeed * delta_time;
    if(IsKeyDown(KEY_DOWN)) 
        angle.y = rotationSpeed * delta_time; 
    if(IsKeyDown(KEY_LEFT)) 
        angle.x = -rotationSpeed * delta_time;
    if(IsKeyDown(KEY_RIGHT)) 
        angle.x = rotationSpeed * delta_time; 

    float currentSpeed = 0.0f;
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
        currentSpeed = speed * delta_time;
    if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))   
        currentSpeed = -speed * delta_time;

    //camera.up = (Vector3){ 0.0f, angle, 0.0f };  
    UpdateCameraPro(&camera, Vector3{ currentSpeed, 0.0f, 0.0f }, Vector3{ angle.x, angle.y, 0.0f }, 0.0f);  // Update camera



    BeginDrawing();
    ClearBackground(RAYWHITE);
    
        BeginMode3D(camera);

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
