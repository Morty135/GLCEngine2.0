#include <GLCInput.h>

float deltaTime;

GLCInput::GLCInput(GLFWwindow* Window)
{
    window = Window;
}

float GLCInput::Horizontal()
{

}
float GLCInput::Vertical()
{

}
glm::vec3 GLCInput::Combined()
{
    
}
void GLCInput::closeOnEsc()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}