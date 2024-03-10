#version 450 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;
in vec2 Texture;

uniform sampler2D diffuse0;
uniform sampler2D specular0;


void main()
{
    // vec4 outClr = (texture(diffuse0, Texture) * 0.9 + texture(specular0, Texture).r * 0.4);
    // FragColor = outClr * vec4(Color, 1.0);
    FragColor = texture(diffuse0, Texture);
} 