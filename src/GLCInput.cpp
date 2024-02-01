#include <GLCInput.h>

GLCInput::GLCInput(GLFWwindow* Window)
{
    window = Window;
}



float horizontalInput = 0.0f;
float verticalInput = 0.0f;



void GLCInput::processInput()
{   
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        horizontalInput = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        horizontalInput = -1.0f;
    }
    else
    {
        horizontalInput = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        verticalInput = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        verticalInput = -1.0f;
    }
    else
    {
        verticalInput = 0.0f;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}



float GLCInput::Horizontal()
{
    return horizontalInput;
}



float GLCInput::Vertical()
{
    return verticalInput;
}



glm::vec3 GLCInput::Combined()
{
    glm::vec3 combinedInput = glm::vec3(0.0f, 0.0f, 0.0f);
    if(horizontalInput != 0.0f && verticalInput != 0.0f)
    {
        combinedInput = glm::vec3(horizontalInput * 0.7071f, verticalInput * 0.7071f, 0.0f);
    }
    else
    {
        combinedInput = glm::vec3(horizontalInput, verticalInput, 0.0f);
    }
    return combinedInput;
}