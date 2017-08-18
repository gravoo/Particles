#pragma once

#include <GameObject.hpp>
#include <GameLevel.hpp>

class GameBuildUnit : public GameObject
{
public:
    GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture sprite,  GameGrid::Location id);
    void move();
    bool changeSelected();
    void setDestinationToTravel(GameObject &gameObject, const GameLevel& object);
    bool selected{false};
private:
    GameObject destination;
    std::vector<GameGrid::Location> path;
};
