#pragma once

#include <stb_image.h>
class Textures
{
public:
Textures();
void load_texture();
unsigned int get_texture_id();
private:
unsigned int texture_id;
};
