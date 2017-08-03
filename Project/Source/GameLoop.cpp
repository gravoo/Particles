#include <GameLoop.hpp>
#include "Utils.hpp"
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameLoop::GameLoop() :
        shader("../Shaders/SimpleShader.vertex.glsl", "../Shaders/SimpleShader.fragment.glsl"),
        shaderA("../Shaders/SimpleShader.vertexA.glsl", "../Shaders/SimpleShader.fragmentA.glsl"),
        woddenWallShader("../Shaders/VertexShader.WoodenWall.glsl", "../Shaders/FragmentShader.WoodenWall.glsl"),
        cubeShader("../Shaders/VertexShader.Cube.glsl", "../Shaders/FragmentShader.WoodenWall.glsl")
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
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
    shader.compile_shaders();
    shaderA.compile_shaders();
    woddenWallShader.compile_shaders();
    cubeShader.compile_shaders();
    geometry.generate_and_bind_buffered_objects();
    texture.load_texture("../Textures/container.jpg", "../Textures/face.jpg");
}

void GameLoop::run_game()
{
    glEnable(GL_DEPTH_TEST);
    woddenWallShader.Use();
    woddenWallShader.set_int("texture1", 0);
    woddenWallShader.set_int("texture2", 1);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    woddenWallShader.setMat4("projection", projection);
    float mixValue{0.8f};

    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        //render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw object with texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id2());
        mixValue = changedMixedValue(window, mixValue);
        woddenWallShader.Use();
        woddenWallShader.set_float("mixValue", mixValue);
        woddenWallShader.generate_perspective();
        glBindVertexArray(geometry.get_Vertex_Array_Object(4));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //check and call events, swap the buffers
        //draw blinking triangle
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GameLoop::~GameLoop()
{
    glfwTerminate();
}


