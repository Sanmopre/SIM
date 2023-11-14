#ifndef RENDER_H
#define RENDER_H

#include "module.h"
#include "raylib.h"
#include <string>
#include "noise/noise.h"

class Render : public Module {
public:
    Render(std::string name);
    virtual ~Render();
    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;

private:
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int targetFPS = 144;
    const float rotationSpeed = 30.0f;
    const float speed = 10.0f;
    std::string windowTitle = "SIM";
    Model model;                 
    Texture2D texture;
    Texture2D texture2;
    Texture2D texture3;
    Texture2D texture4;
    Texture2D texture5;
    Texture2D texture6;
    Texture2D texture7;
    Camera3D camera;

    Vector2 angle = { 0.0f, 0.0f };
};

#endif // RENDER_H
