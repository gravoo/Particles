#pragma once
#include <string>
// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
    Shader();
    void compile_shaders(std::string vertex_shader_source_code, std::string fragment_shader_source_code);
    Shader& Use();
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    GLuint get_shader_id();
private:
    unsigned int compile_vertex_shader(std::string vertex_shader_source_code);
    unsigned int compile_fragment_shader(std::string fragment_shader_source_code);
    bool link_shaders_and_compile();
    bool compiled_succesed(unsigned int shader_id, int success);
    GLuint shader_program;
};
