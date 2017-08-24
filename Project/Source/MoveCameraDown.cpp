#include<MoveCameraDown.hpp>
#include<Camera.hpp>

MoveCameraDown::MoveCameraDown(std::shared_ptr<Camera> camera) : camera(camera)
{
}

void MoveCameraDown::execute()
{
    camera->ProcessKeyboard(Camera_Movement::DOWN);
}

