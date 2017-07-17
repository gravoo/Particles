#include <Shader.hpp>
#include <Utils.hpp>

Shader::Shader()
{
    vertex_shader = read_file("../Shaders/SimpleShader.vertex1.glsl");
    fragment_shader = read_file("../Shaders/SimpleShader.fragment1.glsl");
}
void Shader::Use()
{
    glUseProgram(this->Program);
}
void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}
void Shader::compile_vertex_shader()
{
    vertex_sader_id = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertex_shader.c_str();
    glShaderSource(vertex_sader_id, 1, &vShaderCode, nullptr);
    glCompileShader(vertex_sader_id);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertex_sader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_sader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void Shader::compile_fragment_shader()
{
    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fShaderCode = fragment_shader.c_str();
    glShaderSource(fragment_shader_id, 1, &fShaderCode, nullptr);
    glCompileShader(fragment_shader_id);
    int  success;
    char infoLog[512];
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader_id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::compile_shaders()
{
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



