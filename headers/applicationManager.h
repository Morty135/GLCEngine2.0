#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class applicationManager 
{
    public:
        GLFWwindow* window = nullptr;
        int width = 800;
        int height = 600;

        void framebuffer_size_callback(GLFWwindow* window, int w,int h);

        void processInput();

        applicationManager(int width, int height);

        void Start();

        void Update();

        void fixedUpadate();
};
#endif