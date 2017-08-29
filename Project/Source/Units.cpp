#include<Units.hpp>
#include<DeselectUnit.hpp>
#include<InputHandler.hpp>
#include<GameBuildUnit.hpp>
#include<Texture.hpp>
#include<SpriteRenderer.hpp>

namespace
{
GLboolean detectMouseClick(GameObject &unit, glm::vec2 mouse) // AABB - AABB collision
{
    if(mouse.x>=0&&mouse.y>=0)
    {
        bool collisionX = unit.Position.x + unit.Size.x >= mouse.x && mouse.x >= unit.Position.x;
        bool collisionY = unit.Position.y + unit.Size.y >= mouse.y && mouse.y >= unit.Position.y;
        return collisionX && collisionY;
    }
    return false;
}
}
Units::Units(std::shared_ptr<InputHandler> inputHandler, GameLevel &gameLevel)
: inputHandler(inputHandler), gameLevel(gameLevel)
{
    inputHandler->setDeselectUnitCommand(std::make_shared<DeselectUnit>(selectedUnit));
}

void Units::update(GLfloat deltaTime)
{
    selectedUnit = getSelectedUnit();
    selectedTile = getSelectedTile();
    inputHandler->resetMouseKeyPressPositionInGame();
    if(selectedUnit)
    {
        selectedUnit->setDestinationToTravel(*selectedTile);
    }
    for(auto & buildUnit : buildUnits)
    {
        buildUnit->update(deltaTime);
    }
}

void Units::render(SpriteRenderer &renderer)
{
    for(auto & buildUnit : buildUnits)
    {
        buildUnit->Draw(renderer);
    }

}

void Units::prepare_build_units(std::vector<Texture> texture)
{
    buildUnits.push_back(std::make_shared<GameBuildUnit>(
        glm::vec2(0, 0), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), texture, GameGrid::Location{0, 0}, gameLevel.grid));
    buildUnits.push_back(std::make_shared<GameBuildUnit>(
        glm::vec2(0, 80), glm::vec2(60, 40), glm::vec2(1.75f, 2.5f), texture, GameGrid::Location{0, 1}, gameLevel.grid));
}

std::shared_ptr<GameBuildUnit> Units::getSelectedUnit()
{
    for(auto & buildUnit : buildUnits)
    {
        if(detectMouseClick(*buildUnit, inputHandler->getPositionInGame()))
        {
            buildUnit->selectUnit();
            inputHandler->setDeselectUnitCommand(std::make_shared<DeselectUnit>(buildUnit));
            return buildUnit;
        }
    }
    return selectedUnit;
}
std::shared_ptr<GameObject> Units::getSelectedTile()
{
    for(auto &tile : gameLevel.Bricks)
    {
        if(detectMouseClick(tile, inputHandler->getPositionInGame()))
        {
            return std::make_shared<GameObject>(tile);
        }
    }
    return selectedTile;
}
