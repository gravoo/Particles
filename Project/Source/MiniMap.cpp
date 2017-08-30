#include <MiniMap.hpp>
#include <SpriteRenderer.hpp>
#include <GameGrid.hpp>
#include <Camera.hpp>

MiniMap::MiniMap(std::shared_ptr<GridWithWeights> grid, std::shared_ptr<Camera> camera,  Texture block)
: GameObject(camera->get2DCameraPosition(),
             glm::vec2(camera->getViewWidth()/(grid->width*3.3f), camera->getViewHeight()/(grid->height*3.3f)),
             block), grid(grid), camera(camera)
{

}

void MiniMap::draw(SpriteRenderer & renderer)
{
    for(int i{0}; i < grid->height; i++)
    {
        for(int j{0}; j < grid->width; j++)
        {
            if(grid->passable(GameGrid::Location{j, i}))
            {
               Color = glm::vec3(0.0f, 0.7f, 0.0f);
            }
            else
            {
               Color = glm::vec3(1.0f, 0.0f, 0.0f);
            }
            Position = glm::vec2(Size.x * j, Size.y * i) + glm::vec2(10, 2.05*camera->getViewHeight()/3.0f) + camera->get2DCameraPosition();
            Draw(renderer);
        }
    }
}

void MiniMap::update()
{

}
