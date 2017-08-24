#pragma once
#include<ICommand.hpp>
#include<memory>

class Camera;

class MoveCameraUp : public ICommand
{
public:
    MoveCameraUp(std::shared_ptr<Camera> camera);
    void execute( ) override;
private:
    std::shared_ptr<Camera> camera;
};
