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
    // Vertices coordinates
    GLfloat vertices[] =
    {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };

// Indices for vertices order
    GLuint indices[] =
    {
    0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
    };


    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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


    shaderProgram = Shader("../shaders/default.vert", "../shaders/default.frag");

    VAO1 = VAO();
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
    return true;
}

bool Render::Update(double delta_time) 
{
    std::cout << "Render Update" << std::endl;

    if(glfwWindowShouldClose(window))
        return false;

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();



    return true;
}

void Render::Cleanup() 
{
	VAO1.Delete();
    //VBO1.Delete();
    //EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}


