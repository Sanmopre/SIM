#include "render.h"
#include <iostream>
#include "raylib.h"

Render::Render(std::string name) : Module(name) {

}

Render::~Render() {

}

bool Render::LoadConfig(std::string config_file) {
    return true;
}

bool Render::Start() {
    
    // Initialize the window
    InitWindow(800, 600, "My Window");
    return true;
}

bool Render::Update(double delta_time) {

    // Set the font size and color
    int fontSize = 20;
    Color fontColor = BLACK;

    // Set the text to display
    const char* text = "Hello, world!";

    // Calculate the text position
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    Vector2 textPosition = {(float)(GetScreenWidth() - textSize.x) / 2, (float)(GetScreenHeight() - textSize.y) / 2};

    // Begin drawing
    BeginDrawing();

    // Draw the text
    DrawText(text, textPosition.x, textPosition.y, fontSize, fontColor);

    // End drawing
    EndDrawing();

    // Close the window when the user presses the escape key
    if (IsKeyPressed(KEY_ESCAPE)) {
        return false;
    }

    return true;
}

void Render::Cleanup() {

}
