#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColorFromAttribute; // output a color to the fragment shader
uniform mat4 offsetValue; // we set this variable in the OpenGL code.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * offsetValue * vec4(aPos, 1.0);
    ourColorFromAttribute = aColor; // set ourColor to the input color we got from the vertex data
}
