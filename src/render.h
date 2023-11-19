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
    bool IsPointInViewFrustum(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUp, float fov, Vector3 point);
private:

    int screenWidth = 1920;
    int screenHeight = 1080;
    int targetFPS = 30;
    std::string windowTitle;

    Model model;                 
    Camera3D camera;
};

#endif // RENDER_H
