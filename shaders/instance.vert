#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 offsets[100];

out vec3 Pos;
out vec3 Normal;
out vec3 Color;


void main()
{
    Color = vec3(1.0, 0.7, 1.0);
    Normal = Normal;
    Pos = vec3(model * vec4(aPos, 1.0f));
    mat4 CameraMatrix = projection * view;

    vec2 offset = offsets[gl_InstanceID];
    gl_Position = CameraMatrix * vec4(aPos + vec3(offset, 0.0), 1.0);
}