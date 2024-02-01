#ifndef GLCCAMERA_H
#define GLCCAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLCInput.h>

class GLCCamera
{
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f);

    GLCCamera(GLFWwindow* window);

    glm::mat4 view();

    glm::mat4 projection;
};



#endif