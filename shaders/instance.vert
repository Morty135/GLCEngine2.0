#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 offsets[1000];

out vec3 Pos;
out vec3 Normal;
out vec3 Color;

void main()
{
    Color = vec3(0.4, 0.7, 0.2);
    Normal = Normal;
    vec2 offset = offsets[gl_InstanceID];
    offset = offset * 100;
    Pos = vec3(model * vec4(aPos.x + offset.x , aPos.y, aPos.z + offset.y, 1.0));
    mat4 CameraMatrix = projection * view;
    gl_Position = CameraMatrix * vec4(Pos, 1.0);
}