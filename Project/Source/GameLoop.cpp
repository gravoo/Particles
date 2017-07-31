#include <GameLoop.hpp>
#include "Utils.hpp"
#include <cassert>

GameLoop::GameLoop() :
        shader("../Shaders/SimpleShader.vertex.glsl", "../Shaders/SimpleShader.fragment.glsl"),
        shaderA("../Shaders/SimpleShader.vertexA.glsl", "../Shaders/SimpleShader.fragmentA.glsl"),
        woddenWallShader("../Shaders/VertexShader.WoodenWall.glsl", "../Shaders/FragmentShader.WoodenWall.glsl")
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
    geometry.generate_and_bind_buffered_objects();
//     geometry.generate_and_bind_buffered_and_element_objects();
    texture.load_texture();
}

void GameLoop::run_game()
{
    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        //render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //draw flying triangle
        shader.Use();
        shader.move_shape_with_uniform();
        glBindVertexArray(geometry.get_Vertex_Array_Object(0));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //draw object with texture
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
        woddenWallShader.Use();
        glBindVertexArray(geometry.get_Vertex_Array_Object(3));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //check and call events, swap the buffers
        //draw blinking triangle
        shaderA.Use();
        shaderA.change_color_with_uniform();
        glBindVertexArray(geometry.get_Vertex_Array_Object(1));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GameLoop::~GameLoop()
{
    glfwTerminate();
}


