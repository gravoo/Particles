#include<MoveCameraLeft.hpp>
#include<Camera.hpp>

MoveCameraLeft::MoveCameraLeft(std::shared_ptr<Camera> camera) : camera(camera)
{
}

void MoveCameraLeft::execute()
{
    camera->ProcessKeyboard(Camera_Movement::LEFT);
}
