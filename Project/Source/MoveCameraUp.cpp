#include<MoveCameraUp.hpp>
#include<Camera.hpp>

MoveCameraUp::MoveCameraUp(std::shared_ptr<Camera> camera) : camera(camera)
{
}

void MoveCameraUp::execute()
{
    camera->ProcessKeyboard(Camera_Movement::UP);
}
