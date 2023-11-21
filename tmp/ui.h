#ifndef UI_H
#define UI_H

#include "module.h"
#include "raylib.h"
#include "raygui.h"
#include <string>

class UI : public Module {
public:
    UI(std::string name);
    virtual ~UI();
    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;

    void DrawUi();

private:

    int fontSize = 20; // Size of the
    int spacing = 2; // Spacing between characters
    int verticalSpacing = 2; // Spacing between lines
    Vector2 position = { 60.0f, 60.0f };
    std::string text = "Simulator";
    std::string cameraPositon = "Camera Position: ";
    std::string cameraString = "";
    Font font = { 0 };
};

#endif // UI_H