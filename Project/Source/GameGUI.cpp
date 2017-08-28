#include <GameGUI.hpp>
#include <Camera.hpp>
#include <SpriteRenderer.hpp>


GameGUI::GameGUI(std::shared_ptr<Camera> camera)
: camera(camera)
{

}

void GameGUI::draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(sprite, camera->get2DCameraPosition()+glm::vec2(0, 2*camera->getViewHeight()/3.0f),
                        glm::vec2(camera->getViewWidth(), camera->getViewHeight()/3.0f),
                        rotation, color);
}
