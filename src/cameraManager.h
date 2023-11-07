#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "raylib.h"
#include "module.h"
#include <vector>

class CameraManager : public Module {
public:

    CameraManager();
    ~CameraManager();

    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;

    //Camera3D* GetCamera(uint index);
    Camera3D* GetMainCamera();
private:
    // Private members
    bool m_isRunning;
    std::vector<Camera3D> m_cameras;
};

#endif // CAMERAMANAGER_H
