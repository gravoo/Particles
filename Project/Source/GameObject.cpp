#include<GameObject.hpp>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity,  GameGrid::Location id)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), id(id) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(Sprite, Position, Size, Rotation, Color);
}
