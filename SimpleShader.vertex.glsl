#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1
  
out vec3 ourColor; // Output a color to the fragment shader
uniform float offset;

void main()
{
    gl_Position = vec4(position.x + offset, position.y + offset, position.z + offset, 1.0);
    ourColor = vec3(color.x+offset, color.y + offset, color.z + offset); // Set ourColor to the input color we got from the vertex data
}
