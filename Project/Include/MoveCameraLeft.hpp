#pragma once
#include<ICommand.hpp>
#include<memory>

class Camera;

class MoveCameraLeft : public ICommand
{
public:
    MoveCameraLeft(std::shared_ptr<Camera> camera);
    void execute( ) override;
private:
    std::shared_ptr<Camera> camera;
};


