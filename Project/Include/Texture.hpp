#pragma once

#include <stb_image.h>
#include <string>
#include <glad/glad.h>

class Texture
{
public:
    Texture();
    void generate_texture(GLuint width, GLuint height,  unsigned char* data);
    GLuint get_texture_id();
    void Bind() const;
    GLuint Internal_Format;
    GLuint Image_Format;
    GLuint texture_id;
private:
    GLuint width{0}, height{0};
    GLuint Wrap_S; // Wrapping mode on S axis
    GLuint Wrap_T; // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
};
