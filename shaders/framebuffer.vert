#version 450 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inTexCoords;

out vec2 texCoords;

void main()
{
    gl_position = vec4(inPos.x, inPos.y, 0.0, 1.0);
    texCoords = inTexCoords;
}