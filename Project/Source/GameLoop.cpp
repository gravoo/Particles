#include <GameLoop.hpp>
#include "Utils.hpp"
#include <cassert>

namespace
{
    float yaw = -90.0f, pitch = 0.0f;
    bool firstMouse{true};
    float lastX = 400, lastY = 300;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    float fov = 45.0f;

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        if(fov >= 1.0f && fov <= 90.0f)
            fov -= yoffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 90.0f)
            fov = 90.0f;
    }
}

GameLoop::GameLoop() :
        shader("../Shaders/SimpleShader.vertex.glsl", "../Shaders/SimpleShader.fragment.glsl"),
        shaderA("../Shaders/SimpleShader.vertexA.glsl", "../Shaders/SimpleShader.fragmentA.glsl"),
        woddenWallShader("../Shaders/VertexShader.WoodenWall.glsl", "../Shaders/FragmentShader.WoodenWall.glsl"),
        cubeShader("../Shaders/VertexShader.Cube.glsl", "../Shaders/FragmentShader.WoodenWall.glsl"),
        camera(glm::vec3(0.0f, 0.0f, 3.0f))
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
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

    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        move_camera();
        //render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw object with texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture.get_texture_id2());
        woddenWallShader.Use();
        glBindVertexArray(geometry.get_Vertex_Array_Object(0));
        for(int i{0};i<10;i++)
        {
            woddenWallShader.generate_perspective(i, cameraPos, cameraFront, cameraUp, fov);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //check and call events, swap the buffers
        //draw blinking triangle
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameLoop::move_camera()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
}


GameLoop::~GameLoop()
{
    glfwTerminate();
}
