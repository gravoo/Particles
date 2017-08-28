#include <GameBuildUnit.hpp>
#include <GameLevel.hpp>
#include <iostream>
namespace
{
std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, std::tuple<int,int> loc) {
  int x, y;
  std::tie (x, y) = loc;
  out << '(' << x << ',' << y << ')';
  return out;
}

glm::vec2 getPosition(std::tuple<int,int> loc)
{
    int x, y;
    std::tie (x, y) = loc;
    return glm::vec2(x,y);
}

}
GameBuildUnit::GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::vector<Texture> sprites,  GameGrid::Location id,
                             std::shared_ptr<GridWithWeights> grid)
    : GameObject(pos, size, sprites[0], glm::vec3(1.0f), velocity, id), destination(GameObject()), sprites(sprites), world_grid(grid)
{
    world_grid->walls.insert(id);
    destination.id = id;
}

void GameBuildUnit::update(GLfloat elapsedTime)
{
    if(destination.id != id and !path.empty())
    {
        updateTime -= elapsedTime;
        Position += getDirectionOfMovement();
        if(updateTime <= 0)
        {
            changeSprite();
            world_grid->walls.erase(id);
            id = path.back();
            world_grid->walls.insert(id);
            Position = getPosition(path.back()) * destination.Size;
            path.pop_back();
            updateTime = 0.5;
            find_path();
        }
    }
}

void GameBuildUnit::setDestinationToTravel(GameObject &gameObject)
{
    if(isSelected)
    {
        destination = gameObject;
        find_path();
    }
}

glm::vec2 GameBuildUnit::getDirectionOfMovement()
{
    auto direction = glm::vec2(getPosition(path.back()) - getPosition(id));
    return direction * Velocity;
}

void GameBuildUnit::changeSprite()
{
    Sprite = sprites[current_sprite % sprites.size()];
    current_sprite++;
}

void GameBuildUnit::find_path()
{
    if(destination.id != id)
    {
        std::unordered_map<GameGrid::Location, GameGrid::Location> came_from;
        std::unordered_map<GameGrid::Location, double> cost_so_far;
        if(world_grid->passable(destination.id))
        {
            a_star_search(*world_grid, id, destination.id, came_from, cost_so_far);
            path = reconstruct_path(id, destination.id, came_from, (world_grid->width*world_grid->height - world_grid->walls.size()));
            path.pop_back();
            world_grid->walls.insert(id);
        }
    }
}
void GameBuildUnit::selectUnit()
{
    isSelected = true;
}

void GameBuildUnit::deselectUnit()
{
    isSelected = false;
}


