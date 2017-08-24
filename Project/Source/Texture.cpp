#include <Texture.hpp>
#include <iostream>
#include <stb_image.h>

Texture::Texture()
    : Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &texture_id);
}

void Texture::generate_texture(GLuint width, GLuint height,  unsigned char* data)
{
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::get_texture_id()
{
    return texture_id;
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
