#pragma once
#include<glm/glm.hpp>
#include<Texture.hpp>
#include<SpriteRenderer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    GLfloat     Rotation;
    GLboolean   IsSolid;
    GLboolean   Destroyed;
    Texture   Sprite;
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    virtual void Draw(SpriteRenderer &renderer);
};