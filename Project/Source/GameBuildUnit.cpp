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

void GameBuildUnit::move()
{
    if(!path.empty())
    {
        if(selected)
        {
            id = path.back();
            this->Position = getPosition(path.back()) * destination.Size;
        }
        path.pop_back();
    }
}

bool GameBuildUnit::changeSelected()
{
    destination = GameObject();
    return selected=(selected)?false:true;
}

void GameBuildUnit::setDestinationToTravel(GameObject &gameObject, const GameLevel& level)
{
    destination = gameObject;
    std::unordered_map<GameGrid::Location, GameGrid::Location> came_from;
    std::unordered_map<GameGrid::Location, double> cost_so_far;
    a_star_search(level.grid, id, destination.id, came_from, cost_so_far);
    path = reconstruct_path(id, destination.id, came_from);
    for(auto &x : path)
    {
        std::cout<<x;
    }
    std::cout<<std::endl;
}
