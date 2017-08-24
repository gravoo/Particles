#pragma once
#include<GameBuildUnit.hpp>
#include<GameLevel.hpp>
#include<vector>
#include<memory>
#include<Texture.hpp>
#include<GameGrid.hpp>
#include<SpriteRenderer.hpp>

class InputHandler;

class Units
{
public:
    Units() = default;
    Units(std::shared_ptr<InputHandler> inputHandler, GameLevel &gameLevel);
    void update(GLfloat deltaTime);
    void render(SpriteRenderer &renderer);
    void prepare_build_units(std::vector<Texture> textures);
private:
    std::shared_ptr<GameBuildUnit> getSelectedUnit();
    std::shared_ptr<GameObject> getSelectedTile();
    std::shared_ptr<GameBuildUnit> selectedUnit;
    std::shared_ptr<InputHandler> inputHandler;
    GameLevel gameLevel;
    std::vector<std::shared_ptr<GameBuildUnit>> buildUnits;
    std::shared_ptr<GameObject> selectedTile;
};
