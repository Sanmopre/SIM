#ifndef RENDER_H
#define RENDER_H

#include "module.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"glm/glm.hpp"
#include <string>
#include <vector>



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
    Shader shaderProgram;
	VAO VAO1;

    GLFWwindow* window;
};

#endif // RENDER_H
