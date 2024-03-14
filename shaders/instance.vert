#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 offsets[7000];

out vec3 Pos;
out vec3 Normal;
out vec3 Color;
out vec2 Texture;

void main()
{
    Color = vec3(0.4, 0.7, 0.2);
    Normal = Normal;
    Texture = aTex;
    vec2 offset = offsets[gl_InstanceID];
    offset = offset * 200;
    Pos = vec3(model * vec4(aPos.x + offset.x , aPos.y, aPos.z + offset.y, 1.0));
    mat4 CameraMatrix = projection * view;
    gl_Position = CameraMatrix * vec4(Pos, 1.0);
}