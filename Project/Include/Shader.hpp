#pragma once
#include <string>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    GLuint Program;
    Shader();
    void compile_shaders();
    void Use();
    void set_int(const std::string &name, int value) const;
private:
    unsigned int compile_vertex_shader();
    unsigned int compile_fragment_shader();
    bool compiled_succesed(unsigned int shader_id);
    std::string vertex_shader;
    std::string fragment_shader;
    unsigned int shader_program;
};
