#include <ResourceManager.hpp>
#include <Utils.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stb_image.h>

// Instantiate static variables
std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader>  ResourceManager::Shaders;

Shader ResourceManager::LoadShader(std::string vertex_shader_path, std::string fragment_shader_path, std::string name)
{
    Shaders[name] = loadShaderFromFile(vertex_shader_path, fragment_shader_path);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(std::string texture_path, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(texture_path, alpha);
    return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.get_shader_id());
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.texture_id);
}

Shader ResourceManager::loadShaderFromFile(std::string vertex_shader_path, std::string fragment_shader_path)
{
    std::string vertex_shader_source_code = read_file(vertex_shader_path);
    std::string fragment_shader_source_code = read_file(fragment_shader_path);
    Shader shader;
    shader.compile_shaders(vertex_shader_source_code, fragment_shader_source_code);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(std::string texture_path, GLboolean alpha)
{
    Texture texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        texture.generate_texture(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}
