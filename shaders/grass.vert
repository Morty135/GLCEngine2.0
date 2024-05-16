#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // Removing unused attribute
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offsets[4000]; // Reduced the size of offsets array

out vec3 Pos;
out vec3 Normal;
out vec3 Color;
out vec2 Texture;



void main()
{
    Normal = aNormal;
    Texture = aTex;

    vec3 offset = offsets[gl_InstanceID];
    Color = vec3(0.3, 0.9, 0.1);

    vec4 offsetPos = model * vec4(aPos + offset.xy, 1.0);
    Pos = vec3(offsetPos);

    mat4 CameraMatrix = projection * view;
    gl_Position = CameraMatrix * offsetPos;
}