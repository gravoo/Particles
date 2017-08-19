#pragma once

#include <GameObject.hpp>
#include <GameLevel.hpp>

class GameBuildUnit : public GameObject
{
public:
    GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::vector<Texture> sprites,  GameGrid::Location id);
    void update(GLfloat elapsedTime);
    bool setSelectedFlag(bool selected);
    void setDestinationToTravel(GameObject &gameObject, const GameLevel& object);
    bool selected{false};
private:
    void changeSprite();
    glm::vec2 getDirectionOfMovement();
    GameObject destination;
    GLfloat updateTime{0.0f};
    std::vector<GameGrid::Location> path;
    std::vector<Texture> sprites;
    unsigned char current_sprite{0};
};
