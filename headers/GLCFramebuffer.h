#ifndef GLCFRAMEBUFFER_H
#define GLCFRAMEBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLCShader.h"

class GLCFramebuffer
{
public:

    GLCFramebuffer(int width, int height, int screenWidth, int screenHeight);

    void Bind();

    void Use();

    void Delete();
private:
    std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

    int width, height;
    int screenWidth, screenHeight;

    float rectangleVertices[24] =
    {
        // Coords    // texCoords
        1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,

        1.0f,  1.0f,  1.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
    };
    unsigned int FBO;
    unsigned int RBO;
    unsigned int rectVAO, rectVBO;
    unsigned int framebufferTexture;

    GLCShader framebufferProgram;
};


#endif