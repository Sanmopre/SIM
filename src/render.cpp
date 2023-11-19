#include "render.h"
#include "engine.h"
#include "ui.h"
#include <iostream>
#include <fstream>

Render::Render(std::string name) : Module(name) 
{
}

Render::~Render() {

}

bool Render::LoadConfig(std::string config_file) 
{
    std::ifstream file(config_file);
    json j;
    file >> j;

    screenWidth = j["windowWidth"].get<int>();
    screenHeight = j["windowHeight"].get<int>();
    targetFPS = j["targetFPS"].get<int>();
    windowTitle = j["windowTitle"].get<std::string>();

    InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    SetTargetFPS(targetFPS);
    return true;
}

bool Render::Start() 
{
    camera.position = Vector3{ 0.0f, 200.0f, 1.0f };  // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    //model = LoadModel("../models/plane.obj");                 // Load model

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
        //DrawModel(model, Vector3{ 0.0f, 30.0f, 0.0f }, 1.0f, WHITE);
        EndMode3D();
        engine->ui->DrawUi();
    EndDrawing();

    return true;
}

void Render::Cleanup() 
{
    CloseWindow();
}


// Subtracts one vector from another
Vector3 Vector3Subtract(Vector3 v1, Vector3 v2)
{
    Vector3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

// Normalizes a vector (makes its length 1)
void Vector3Normalize(Vector3* v)
{
    float length = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

// Calculates the dot product of two vectors
float Vector3DotProduct(Vector3 v1, Vector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

bool Render::IsPointInViewFrustum(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUp, float fov, Vector3 point)
{
    // Calculate the forward vector from the camera position to the target
    Vector3 cameraForward = Vector3Subtract(cameraTarget, cameraPosition);
    Vector3Normalize(&cameraForward);

    // Calculate the direction vector from the camera to the point
    Vector3 direction = Vector3Subtract(point, cameraPosition);
    Vector3Normalize(&direction);

    // Calculate the dot product of the direction and the camera's forward vector
    float dotProduct = Vector3DotProduct(direction, cameraForward);

    // Calculate the angle between the direction and the camera's forward vector
    float angle = acosf(dotProduct);

    // If the angle is less than half of the FOV, the point is within the camera's view
    return angle < fov / 2.0f;
}


