#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SpriteRenderer.hpp>
#include <GameObject.hpp>
#include <ResourceManager.hpp>
#include <GameGrid.hpp>
#include <memory>

class GameLevel
{
public:
    std::vector<GameObject> Bricks;
    GameLevel() { }
    void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void Draw(SpriteRenderer &renderer);
    GLboolean IsCompleted();
    void checkWithTileWasClicked();
    std::shared_ptr<GridWithWeights> grid;
private:
    void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};
