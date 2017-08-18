#include<GameBuildUnit.hpp>
#include<iostream>
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
GameBuildUnit::GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture sprite,  GameGrid::Location id)
    : GameObject(pos, size, sprite, glm::vec3(1.0f), velocity, id), destination(GameObject())
{

}

void GameBuildUnit::update(GLfloat elapsedTime)
{
    if(!path.empty())
    {
        updateTime -= elapsedTime;
        if(updateTime <= 0)
        {
            id = path.back();
            this->Position = getPosition(path.back()) * destination.Size;
            path.pop_back();
            updateTime = 0.5;
        }
    }
}

bool GameBuildUnit::setSelectedFlag(bool selected)
{
    this->selected = selected;
    return selected;
}

void GameBuildUnit::setDestinationToTravel(GameObject &gameObject, const GameLevel& level)
{
    destination = gameObject;
    std::unordered_map<GameGrid::Location, GameGrid::Location> came_from;
    std::unordered_map<GameGrid::Location, double> cost_so_far;
    a_star_search(level.grid, id, destination.id, came_from, cost_so_far);
    path = reconstruct_path(id, destination.id, came_from);
}
