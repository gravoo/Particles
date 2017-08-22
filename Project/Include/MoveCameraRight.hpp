#pragma once
#include<ICommand.hpp>
#include<Camera.hpp>
#include<memory>
class MoveCameraRight: public ICommand
{
public:
    MoveCameraRight(std::shared_ptr<Camera> camera) : camera(camera)
    {}
    void execute( ) override
    {
        camera->ProcessKeyboard(Camera_Movement::RIGHT);
    };
private:
    std::shared_ptr<Camera> camera;
};



