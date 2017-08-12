#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Game.hpp>
#include <cassert>
#include <ResourceManager.hpp>

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_buttonCallback(GLFWwindow* window, int key, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Game game{SCREEN_WIDTH, SCREEN_HEIGHT};
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        assert(false);
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        assert(false);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_buttonCallback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    game.Init();
    // DeltaTime variables

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            game.keys[key] = GL_FALSE;
    }
}
void mouse_buttonCallback(GLFWwindow* window, int key, int action, int mods)
{
    if (key == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            game.keys[key] = GL_TRUE;
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            game.setMousePosition(x, y);
        }
        else if (action == GLFW_RELEASE)
            game.keys[key] = GL_FALSE;
    }
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    game.setLastMousePosition(xpos, ypos);
}
