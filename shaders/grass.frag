#version 450 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;

uniform sampler2D diffuse0;
uniform sampler2D specular0;


void main()
{
    FragColor = vec4(Color, 1.0);
} 