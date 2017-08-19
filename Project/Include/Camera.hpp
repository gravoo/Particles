#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

enum class Camera_Movement {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera(glm::vec3 position, GLuint width, GLuint height,  GLfloat rotate);
    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    glm::vec2 GetCameraCord();
    glm::mat4 getProjectionMatrix();
    float Zoom;
private:
    void updateCameraVectors();
    glm::vec3 Position;
    glm::vec3 Front{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 Up{glm::vec3(0.0f, 1.0f, 0.0f)};
    glm::vec3 Right;
    glm::vec3 WorldUp{0.0f, 1.0f, 0.0f};
    float Yaw{-90.0f};
    float Pitch{0.0f};
    float MovementSpeed{100.f};
    GLuint width{800}, height{600};
    GLfloat rotate{0.0f};
};
