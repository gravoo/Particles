#include <GameGUI.hpp>
#include <SpriteRenderer.hpp>
#include <MiniMap.hpp>
#include <GameObject.hpp>

GameGUI::GameGUI(std::shared_ptr<MiniMap> miniMap, std::shared_ptr<GameObject> background)
: miniMap(miniMap), background(background)
{

}

void GameGUI::draw(SpriteRenderer &renderer)
{
    miniMap->draw(renderer);
    background->Draw(renderer);

}

void GameGUI::update(glm::vec2 cameraCord)
{
    background->Position = cameraCord;
}
