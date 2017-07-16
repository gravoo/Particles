#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    GLuint Program;
    Shader();
    void Use();
    void set_int(const std::string &name, int value) const;
};
