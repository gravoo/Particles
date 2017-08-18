#pragma once

#include <GameObject.hpp>
#include <GameLevel.hpp>

class GameBuildUnit : public GameObject
{
public:
    GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture sprite,  GameGrid::Location id);
    void update(GLfloat elapsedTime);
    bool setSelectedFlag(bool selected);
    void setDestinationToTravel(GameObject &gameObject, const GameLevel& object);
    bool selected{false};
private:
    GameObject destination;
    GLfloat updateTime{0.0f};
    std::vector<GameGrid::Location> path;
};
