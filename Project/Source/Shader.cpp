#include <Shader.hpp>
#include <Utils.hpp>
#include <cassert>
#include <cmath>


Shader::Shader()
{
}
Shader &Shader::Use()
{
    glUseProgram(shader_program);
    return *this;
}

GLuint Shader::get_shader_id()
{
    return shader_program;
}

unsigned int Shader::compile_vertex_shader(std::string vertex_shader_source_code)
{
    unsigned int vertex_sader_id = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertex_shader_source_code.c_str();
    glShaderSource(vertex_sader_id, 1, &vShaderCode, nullptr);
    glCompileShader(vertex_sader_id);
    if(!compiled_succesed(vertex_sader_id))
    {
        assert(false);
        std::cout << "ERROR::VERTEX_SHADER\n";
        return 0;
    }
    return vertex_sader_id;
}

unsigned int Shader::compile_fragment_shader(std::string fragment_shader_source_code)
{
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fShaderCode = fragment_shader_source_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fShaderCode, nullptr);
    glCompileShader(fragment_shader_id);
    if(!compiled_succesed(fragment_shader_id))
    {
        std::cout << "ERROR::FRAGMENT_SHADER\n";
        return 0;
    }
    return fragment_shader_id;
}

void Shader::compile_shaders(std::string vertex_shader_source_code, std::string fragment_shader_source_code)
{
    unsigned int vertex_sader_id = compile_vertex_shader(vertex_shader_source_code);
    unsigned int fragment_shader_id = compile_fragment_shader(fragment_shader_source_code);
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_sader_id);
    glAttachShader(shader_program, fragment_shader_id);
    glLinkProgram(shader_program);
    if(!compiled_both_succesed(shader_program))
    {
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n";
    }
    glDeleteShader(vertex_sader_id);
    glDeleteShader(fragment_shader_id);
}

bool Shader::compiled_succesed(unsigned int shader_id)
{
    int  success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    char infoLog[512];
    if(!success)
    {
        glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::compiled_both_succesed(unsigned int shader_id)
{
    int  success;
    GLchar infoLog[1024];
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_id, 1024, NULL, infoLog);
        std::cout << "| ERROR::Shader: Link-time error: " << "\n"
        << infoLog << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
}

void Shader::SetMatrix4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetInteger(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
}

void Shader::SetVector3f (const std::string &name, const glm::vec3 &value) const
{
    glUniform3f(glGetUniformLocation(shader_program, name.c_str()), value.x, value.y, value.z);
}
void Shader::SetVector3f(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) const
{
    glUniform3f(glGetUniformLocation(shader_program, name.c_str()), x, y, z);
}


