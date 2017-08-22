#pragma once
#include<ICommand.hpp>
#include<Camera.hpp>
#include<memory>
class MoveCameraUp : public ICommand
{
public:
    MoveCameraUp(std::shared_ptr<Camera> camera) : camera(camera)
    {}
    void execute( ) override
    {
        camera->ProcessKeyboard(Camera_Movement::UP);
    };
private:
    std::shared_ptr<Camera> camera;
};
