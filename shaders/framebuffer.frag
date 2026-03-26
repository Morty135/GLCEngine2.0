#version 450 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;
uniform float time;

void main()
{
    vec2 uv = texCoords;

    // --- Curvature ---
    vec2 centered = uv * 2.0 - 1.0;
    float strength = 0.2; // slightly reduced
    centered *= 1.0 + strength * dot(centered, centered);
    uv = centered * 0.5 + 0.5;

    if(uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        FragColor = vec4(0.0);
        return;
    }

    // --- Chromatic aberration ---
    float offset = 0.0015;
    float r = texture(screenTexture, uv + vec2(offset, 0.0)).r;
    float g = texture(screenTexture, uv).g;
    float b = texture(screenTexture, uv - vec2(offset, 0.0)).b;

    vec3 color = vec3(r, g, b);

    // --- Scanlines ---
    float scanline = sin(uv.y * 700.0) * 0.03;
    color -= scanline;

    // --- Smaller vignette ---
    float vignette = smoothstep(1.2, 0.4, length(centered));
    color *= vignette;

    // --- Flicker ---
    float flicker = sin(time * 12.0) * 0.02;
    color += flicker;

    FragColor = vec4(color, 1.0);
}
