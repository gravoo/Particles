#include <Shader.hpp>
#include <cassert>
#include <Utils.hpp>

Shader::Shader()
{
    std::cout<<"DUPA";
    std::string vertex_shader = read_file("../Shaders/SimpleShader.vertex1.glsl");
    std::cout<<vertex_shader;
}
void Shader::Use()
{
    glUseProgram(this->Program);
}
void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}


