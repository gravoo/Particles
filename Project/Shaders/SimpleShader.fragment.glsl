#version 330 core
out vec4 FragColor;
in vec3 ourColorFromAttribute;

void main()
{
    FragColor = vec4(ourColorFromAttribute, 1.0);
}
