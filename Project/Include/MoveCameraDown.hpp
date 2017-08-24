#pragma once
#include<ICommand.hpp>
#include<memory>

class Camera;

class MoveCameraDown : public ICommand
{
public:
    MoveCameraDown(std::shared_ptr<Camera> camera);
    void execute( ) override;
private:
    std::shared_ptr<Camera> camera;
};

