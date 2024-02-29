#ifndef GLCInput_H
#define GLCInput_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLCInput
{
public:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);

    GLFWwindow* window = nullptr;

    GLCInput(GLFWwindow* Window);

    void processInput();

    float Horizontal();
    float Vertical();
    glm::vec3 Combined();

};



#endif