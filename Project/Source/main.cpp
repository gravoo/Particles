#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Game.hpp>
#include <cassert>
#include <ResourceManager.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_buttonCallback(GLFWwindow* window, int key, int action, int mods);
GLFWwindow* glfwInitialFunctions();
void glInitialFunctions();

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
Game game{SCREEN_WIDTH, SCREEN_HEIGHT};
int main()
{
    GLFWwindow* window = glfwInitialFunctions();
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        assert(false);
    }
    glInitialFunctions();
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_buttonCallback);

    game.Init();

    while(!glfwWindowShouldClose(window))
    {
        game.SyncroinzeTimers();
        glfwPollEvents();
        game.ProcessInput();
        game.UpdateState();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.Render();
        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    glfwTerminate();
}


GLFWwindow* glfwInitialFunctions()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        assert(false);
    }
    return window;
}

void glInitialFunctions()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            game.setKeyInput(key);
        }
        else if (action == GLFW_RELEASE)
        {
            game.unsetKeyInput(key);
        }
    }
}
void mouse_buttonCallback(GLFWwindow* window, int key, int action, int mods)
{
    if(key >= 0 && key < 9)
    {
        if (action == GLFW_PRESS)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            game.setMouseInput(key, x, y);
        }
        else if (action == GLFW_RELEASE)
        {
            game.unsetMouseInput(key);

        }
    }
}
