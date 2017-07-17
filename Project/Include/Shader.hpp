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
    void compile_vertex_shader();
    void compile_fragment_shader();
    void compile_shaders();
    void Use();
    void set_int(const std::string &name, int value) const;
private:
    std::string vertex_shader;
    std::string fragment_shader;
    unsigned int fragment_shader_id;
    unsigned int vertex_sader_id;
    unsigned int shader_program;
};
