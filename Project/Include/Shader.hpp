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
    Shader(std::string path_to_vertex_shader, std::string path_to_fragment_shader);
    void compile_shaders();
    void Use();
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void change_color_with_uniform() const;
    void move_shape_with_uniform(const std::string &name) const;
    void rotate_left(const std::string &name) const;
    void generate_perspective(const unsigned int index, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) const;
    void rotate_cube(int i) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
    unsigned int compile_vertex_shader();
    unsigned int compile_fragment_shader();
    bool compiled_succesed(unsigned int shader_id);
    std::string vertex_shader;
    std::string fragment_shader;
    unsigned int shader_program;
};
