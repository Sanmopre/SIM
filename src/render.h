#ifndef RENDER_H
#define RENDER_H

#include "module.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>



class Render : public Module {
public:
    Render(std::string name);
    virtual ~Render();
    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;
private:

    int screenWidth = 1920;
    int screenHeight = 1080;
    int targetFPS = 30;
    std::string windowTitle;
    
    GLuint shaderProgram;
    GLuint VAO, VBO;
    GLFWwindow* window;



    // Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";
};

#endif // RENDER_H
