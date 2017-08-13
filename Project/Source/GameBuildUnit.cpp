#include<GameBuildUnit.hpp>
#include<iostream>

GameBuildUnit::GameBuildUnit(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture sprite)
    : GameObject(pos, size, sprite, glm::vec3(1.0f), velocity), destination(glm::vec2(0.0f, 0.0f))
{

}

void GameBuildUnit::move(glm::vec2 pos, GLfloat dt)
{
    if(selected)
    {
        if(destination.x && destination.y)
        {
            std::cout<<Position.x<<" "<<Position.y<<std::endl;
            std::cout<<destination.x<<" "<<destination.y<<std::endl;
            Position = destination;
        }
    }
}

bool GameBuildUnit::changeSelected()
{
    destination = glm::vec2(0, 0);
    return selected=(selected)?false:true;
}

void GameBuildUnit::setDestinationToTravel(glm::vec2 pos)
{
    destination = pos;
}
