#pragma once

#include <map>
#include <string>
#include <Shader.hpp>
#include <Texture.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ResourceManager
{
public:
    ResourceManager() = delete;
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture>  Textures;
    static Shader   LoadShader(std::string vertex_shader_path, std::string fragment_shader_path, std::string name);
    static Shader   GetShader(std::string name);
    static Texture LoadTexture(std::string texture_path, GLboolean alpha, std::string name);
    static Texture GetTexture(std::string name);
    static void  Clear();
private:
    static Shader    loadShaderFromFile(std::string vertex_shader_path, std::string fragment_shader_path);
    static Texture loadTextureFromFile(std::string texture_path, GLboolean alpha);
};
