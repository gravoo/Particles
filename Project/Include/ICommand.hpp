#pragma once
#include <GLFW/glfw3.h>
class ICommand
{
public:
    virtual ~ICommand(){}
    virtual void execute() = 0;
};
