#version 330 core
out vec4 FragColor;

in vec3 a_color;

void main()
{
    FragColor = vec4(a_color, 1.0);
}
