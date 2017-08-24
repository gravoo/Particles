#pragma once
#include<ICommand.hpp>
#include<memory>

class Camera;

class MoveCameraRight: public ICommand
{
public:
    MoveCameraRight(std::shared_ptr<Camera> camera);
    void execute( ) override;
private:
    std::shared_ptr<Camera> camera;
};



