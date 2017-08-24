#include<MoveCameraRight.hpp>
#include<Camera.hpp>

MoveCameraRight::MoveCameraRight(std::shared_ptr<Camera> camera) : camera(camera)
{}
void MoveCameraRight::execute( )
{
    camera->ProcessKeyboard(Camera_Movement::RIGHT);
};
