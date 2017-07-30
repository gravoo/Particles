#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColorFromAttribute; // output a color to the fragment shader
uniform vec3 offsetValue; // we set this variable in the OpenGL code.

void main()
{
    gl_Position = vec4(aPos.x + offsetValue.x, aPos.y+offsetValue.y, aPos.z, 1.0);
    ourColorFromAttribute = aPos + offsetValue; // set ourColor to the input color we got from the vertex data
}
