#pragma once

#include <GameObject.hpp>

class BallObject : public GameObject
{
public:
BallObject();
BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture sprite);
GLfloat   Radius;
GLboolean Stuck;
glm::vec2 Move(GLfloat dt, GLuint window_width);
void      Reset(glm::vec2 position, glm::vec2 velocity);
};
