#pragma once
#include <memory>
#include <GameObject.hpp>

class SpriteRenderer;
class GridWithWeights;
class Camera;

class MiniMap : public GameObject
{
public:
    MiniMap(std::shared_ptr<GridWithWeights> grid, std::shared_ptr<Camera> camera,  Texture block);
    void draw(SpriteRenderer &renderer);
    void update();
private:
    std::shared_ptr<GridWithWeights> grid;
    std::shared_ptr<Camera> camera;
};
