#include "cameraManager.h"

CameraManager::CameraManager() : Module("cameraManager")
{
    m_isRunning = false;
}

CameraManager::~CameraManager()
{
    Cleanup();
}  

bool CameraManager::LoadConfig(std::string config_file)
{
    return true;
}

bool CameraManager::Start()
{
    Camera3D camera;
    camera.position = { 0.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };

    m_cameras.push_back(camera);

    return true;
}

bool CameraManager::Update(double delta_time)
{
    for(auto cam : m_cameras)
    {
        UpdateCamera(&cam, CAMERA_CUSTOM);
    }
    return true;
}

void CameraManager::Cleanup()
{
    m_cameras.clear();
}