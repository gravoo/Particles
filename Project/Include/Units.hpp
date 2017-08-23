#pragma once
#include<GameBuildUnit.hpp>
#include<GameLevel.hpp>
#include<InputHandler.hpp>
#include<vector>
#include<memory>
#include<Texture.hpp>
#include<GameGrid.hpp>
#include<SpriteRenderer.hpp>
class Units
{
public:
    Units() = default;
    Units(InputHandler &inputHandler, GameLevel &gameLevel);
    void update(GLfloat deltaTime);
    void render(SpriteRenderer &renderer);
    void prepare_build_units(std::vector<Texture> textures);
private:
    std::shared_ptr<GameBuildUnit> getSelectedUnit();
    std::shared_ptr<GameObject> getSelectedTile();
    InputHandler inputHandler;
    GameLevel gameLevel;
    std::vector<std::shared_ptr<GameBuildUnit>> buildUnits;
    std::shared_ptr<GameBuildUnit> selectedUnit;
    std::shared_ptr<GameObject> selectedTile;
};
