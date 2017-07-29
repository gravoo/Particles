#pragma once
#include <iostream>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <Geometry.hpp>

class GameLoop
{
public:
    GameLoop();
    void run_game();
    ~GameLoop();

private:
    GLFWwindow* window;
    int width{800};
    int height{600};
    std::string window_name{"Particles"};
    Shader shader;
    Geometry geometry;
};

