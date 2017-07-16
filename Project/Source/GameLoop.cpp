#include "GameLoop.hpp"
#include "Utils.hpp"

GameLoop::GameLoop()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

void GameLoop::run_game()
{
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        //render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //check and call events, swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

GameLoop::~GameLoop()
{
    glfwTerminate();
}


