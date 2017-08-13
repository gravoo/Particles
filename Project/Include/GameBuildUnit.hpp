#pragma once

#include <GameObject.hpp>

class GameBuildUnit : public GameObject
{
public:
    GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture sprite);
    void move(glm::vec2 pos, GLfloat dt);
    bool changeSelected();
    void setDestinationToTravel(glm::vec2 pos);
    bool selected{false};
private:
    glm::vec2  destination;
};
