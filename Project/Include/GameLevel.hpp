#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ResourceManager.hpp>
#include <memory>

class GridWithWeights;
class GameObject;
class SpriteRenderer;
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
