#pragma once

#include <stb_image.h>
#include <string>
class Textures
{
public:
Textures();
void load_texture(std::string texture_path, std::string texture_path2);
unsigned int get_texture_id();
unsigned int get_texture_id2();
private:
void load_and_generate_texture(std::string texture_path);
unsigned int texture_id;
unsigned int texture_id2;
};
