#pragma once

#include <GameObject.hpp>
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Texture;
class GridWithWeights;

class GameBuildUnit : public GameObject
{
public:
    GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::vector<Texture> sprites,
                  GameGrid::Location id, std::shared_ptr<GridWithWeights> grid);
    void update(GLfloat elapsedTime);
    void setDestinationToTravel(GameObject &gameObject);
private:
    void changeSprite();
    void find_path();
    glm::vec2 getDirectionOfMovement();
    GameObject destination;
    GLfloat updateTime{0.0f};
    std::vector<GameGrid::Location> path;
    std::vector<Texture> sprites;
    unsigned char current_sprite{0};
    std::shared_ptr<GridWithWeights> world_grid;
};
