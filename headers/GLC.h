#ifndef GLC_H
#define GLC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//my parts
#include <GLCShader.h>
#include <GLCCamera.h>
#include <GLCMesh.h>
#include <GLCInput.h>
#include <GLCTexture.h>

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