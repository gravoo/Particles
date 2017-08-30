#include <Camera.hpp>

Camera::Camera( glm::vec3 position, GLuint width, GLuint height,  GLfloat rotate)
        : Position(position), width(width), height(height), rotate(rotate)
{
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::rotate(glm::lookAt(Position, Position + Front, Up), rotate, glm::vec3(0.0f, 0.0f, 1.0f));
}
glm::mat4 Camera::getProjectionMatrix()
{
    return glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 100.0f);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}
void Camera::ProcessKeyboard(Camera_Movement direction)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        Position += Right * velocity;
    if (direction == Camera_Movement::UP)
    {
        Position -= Up * velocity;
    }
    if (direction == Camera_Movement::DOWN)
        Position += Up * velocity;
}
void Camera::update(GLfloat deltaTime)
{
    this->deltaTime=deltaTime;
}

glm::vec4 Camera::getViewport()
{
    return glm::vec4(0, 0, width, height);
}

GLuint Camera::getViewHeight()
{
    return height;
}

GLuint Camera::getViewWidth()
{
    return width;
}

glm::vec2 Camera::get2DCameraPosition()
{
    return glm::vec2(Position.x, Position.y);
}

void Camera::setRotations(GLfloat rotate)
{
    this->rotate = rotate;
}

