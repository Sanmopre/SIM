#include "render.h"
#include "engine.h"
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

    //InitWindow(screenWidth, screenHeight, windowTitle.c_str());
    //SetTargetFPS(targetFPS);
    return true;
}

bool Render::Start() 
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};


    window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    //Tell GLFW to make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);
    gladLoadGL();

    //Set glViewport to the size of the window
    glViewport(0, 0, screenWidth, screenHeight);


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader); //Compile the vertex shader
    //Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //Check if the vertex shader compiled successfully
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //If it didn't, get the info log
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl; //Print the info log
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Create the fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //Set the source code for the fragment shader
    glCompileShader(fragmentShader); //Compile the fragment shader
    //Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); //Check if the fragment shader compiled successfully
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); //If it didn't, get the info log
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; //Print the info log
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


















    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //Tell OpenGL how to interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

bool Render::Update(double delta_time) 
{
    std::cout << "Render Update" << std::endl;

    if(glfwWindowShouldClose(window))
        return false;

    //Poll for events like key presses
    glfwPollEvents();
    //Clear the screen to green
    glClearColor(0.0f, 0.2f, 0.0f, 1.0f); //Set the clear color to black
    glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer (background)

    glUseProgram(shaderProgram); //Use the shader program when we want to render an object

    glBindVertexArray(VAO); //Bind the Vertex Array Object we want to draw

    glDrawArrays(GL_TRIANGLES, 0, 3); //Draw the vertices

    
    //Swap the buffers
    glfwSwapBuffers(window);



    return true;
}

void Render::Cleanup() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


