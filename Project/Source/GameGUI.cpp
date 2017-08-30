#include <GameGUI.hpp>
#include <Camera.hpp>
#include <SpriteRenderer.hpp>
#include <MiniMap.hpp>

GameGUI::GameGUI(std::shared_ptr<Camera> camera, Texture sprite, std::shared_ptr<MiniMap> miniMap)
: camera(camera), sprite(sprite), miniMap(miniMap)
{

}

void GameGUI::draw(SpriteRenderer &renderer)
{
    miniMap->draw(renderer);
    renderer.DrawSprite(sprite,
                        camera->get2DCameraPosition()+glm::vec2(0, 2*camera->getViewHeight()/3.0f),
                        glm::vec2(camera->getViewWidth(), camera->getViewHeight()/3.0f),
                        rotation, color);
}
