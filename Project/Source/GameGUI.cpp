#include <GameGUI.hpp>
#include <Camera.hpp>
#include <SpriteRenderer.hpp>
#include <GameGrid.hpp>
#include <iostream>

GameGUI::GameGUI(std::shared_ptr<Camera> camera, Texture sprite, std::shared_ptr<GridWithWeights> grid, Texture block)
: camera(camera), sprite(sprite), grid(grid), block(block)
{

}

void GameGUI::draw(SpriteRenderer &renderer)
{
    prepareMiniMap(renderer);
    renderer.DrawSprite(sprite,
                        camera->get2DCameraPosition()+glm::vec2(0, 2*camera->getViewHeight()/3.0f),
                        glm::vec2(camera->getViewWidth(), camera->getViewHeight()/3.0f),
                        rotation, color);
}

void GameGUI::prepareMiniMap(SpriteRenderer &renderer)
{
    glm::vec3 color{1.0f};
    GLfloat unit_width{(camera->getViewWidth()/grid->width)/3.3f};
    GLfloat unit_height{(camera->getViewHeight()/grid->height)/3.3f};
    glm::vec2 size(unit_width, unit_height);
    for(int i{0}; i < grid->height; i++)
    {
        for(int j{0}; j < grid->width; j++)
        {
            if(grid->passable(GameGrid::Location{j, i}))
            {
               color = glm::vec3(0.2f, 0.6f, 1.0f);
            }
            else
            {
               color = glm::vec3(1.0f, 0.0f, 0.0f);
            }
            glm::vec2 pos = glm::vec2(unit_width * j, unit_height * i) + glm::vec2(10, 2.05*camera->getViewHeight()/3.0f);
            pos += camera->get2DCameraPosition();
            renderer.DrawSprite(block, pos, size, rotation, color);
        }
    }

}
