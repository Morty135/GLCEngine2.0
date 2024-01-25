#ifndef GLC_H
#define GLC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//my parts
#include <GLCShader.h>
#include <VAO.h>
#include <VBO.h>

class GLC 
{
    public:
        GLFWwindow* window = nullptr;
        int width = 800;
        int height = 600;

        void processInput();

        GLC(int width, int height);
};
#endif