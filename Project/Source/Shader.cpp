#include <Shader.hpp>
#include <Utils.hpp>
#include <cassert>
#include <cmath>

Shader::Shader()
{
    vertex_shader = read_file("../Shaders/SimpleShader.vertex1.glsl");
    fragment_shader = read_file("../Shaders/SimpleShader.fragment1.glsl");
}

Shader::Shader(std::string path_to_fragment_shader)
{
    vertex_shader = read_file("../Shaders/SimpleShader.vertex1.glsl");
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
        std::cout << "ERROR::SHADER::FRAGMENT::OR::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
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



