#include <Shader.hpp>
#include <Utils.hpp>
#include <cassert>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string path_to_vertex_shader, std::string path_to_fragment_shader)
{
    vertex_shader = read_file(path_to_vertex_shader);
    fragment_shader = read_file(path_to_fragment_shader);
}
void Shader::Use()
{
    glUseProgram(shader_program);
}
void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
}
void Shader::rotate_left(const std::string &name) const
{
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}

unsigned int Shader::compile_vertex_shader()
{
    unsigned int vertex_sader_id = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertex_shader.c_str();
    glShaderSource(vertex_sader_id, 1, &vShaderCode, nullptr);
    if(!compiled_succesed(vertex_sader_id))
    {
        return 0;
    }
    return vertex_sader_id;
}

unsigned int Shader::compile_fragment_shader()
{
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fShaderCode = fragment_shader.c_str();
    glShaderSource(fragment_shader_id, 1, &fShaderCode, nullptr);
    if(!compiled_succesed(fragment_shader_id))
    {
        return 0;
    }
    return fragment_shader_id;
}

void Shader::compile_shaders()
{
    unsigned int vertex_sader_id = compile_vertex_shader();
    unsigned int fragment_shader_id = compile_fragment_shader();
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_sader_id);
    glAttachShader(shader_program, fragment_shader_id);
    glLinkProgram(shader_program);
    int  success;
    char infoLog[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex_sader_id);
    glDeleteShader(fragment_shader_id);
}

bool Shader::compiled_succesed(unsigned int shader_id)
{
    glCompileShader(shader_id);
    int  success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void Shader::change_color_with_uniform() const
{
    float timeValue = glfwGetTime();
    float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
    glUseProgram(shader_program);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void Shader::move_shape_with_uniform(const std::string &name) const
{
    float timeValue = glfwGetTime();
    float x_coordin = (std::sin(timeValue));
    glm::mat4 trans;
    trans = glm::scale(trans, glm::vec3(x_coordin, x_coordin, x_coordin));
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}

