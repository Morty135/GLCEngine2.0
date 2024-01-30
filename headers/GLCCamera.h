#ifndef GLCCAMERA_H
#define GLCCAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLCCamera
{
public:
    GLCCamera(GLFWwindow* window);

    void processInput(GLFWwindow *window, float deltaTime);

    glm::mat4 view();

    glm::mat4 projection;
};



#endif