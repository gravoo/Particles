#pragma once
#include <iostream>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.hpp>
#include <Geometry.hpp>
#include <Textures.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    void move_camera();
    Shader shader;
    Shader shaderA;
    Shader woddenWallShader;
    Shader cubeShader;
    Geometry geometry;
    Textures texture;
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

};

