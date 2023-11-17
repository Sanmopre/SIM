#ifndef RENDER_H
#define RENDER_H

#include "module.h"
#include "raylib.h"
#include <string>

class Render : public Module {
public:
    Render(std::string name);
    virtual ~Render();
    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;
    Camera3D* GetCamera() { return &camera; }

private:
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int targetFPS = 144;
    const float rotationSpeed = 30.0f;
    const float speed = 10.0f;
    std::string windowTitle = "SIM";

    
    Model model;                 
    Camera3D camera;

    Vector2 angle = { 0.0f, 0.0f };
};

#endif // RENDER_H
