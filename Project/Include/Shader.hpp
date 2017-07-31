#pragma once
#include <string>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(std::string path_to_vertex_shader, std::string path_to_fragment_shader);
    void compile_shaders();
    void Use();
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void change_color_with_uniform() const;
    void move_shape_with_uniform() const;
private:
    unsigned int compile_vertex_shader();
    unsigned int compile_fragment_shader();
    bool compiled_succesed(unsigned int shader_id);
    std::string vertex_shader;
    std::string fragment_shader;
    unsigned int shader_program;
};
