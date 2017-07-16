#include <Shader.hpp>
#include <cassert>
Shader::Shader()
{
    const GLchar *vertexPath = "../Shaders/SimpleShader.vertex1.glsl";

}
void Shader::Use()
{
    glUseProgram(this->Program);
}
void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}
