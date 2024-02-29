#include <GLCInput.h>

GLCInput::GLCInput(GLFWwindow* Window)
{
    window = Window;
}


float maxSpeed = 2.0f;
float acceleration = 0.05f;

float horizontalInput = 0.0f;
float verticalInput = 0.0f;



void GLCInput::processInput()
{   
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if(horizontalInput < maxSpeed)
        {
            horizontalInput += acceleration;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if(horizontalInput > -maxSpeed)
        {
            horizontalInput -= acceleration;
        }
    }
    else
    {
        if(horizontalInput > 0)
        {
            horizontalInput -= acceleration;
        }
        else if(horizontalInput < 0)
        {
            horizontalInput += acceleration;
        }
        else
        {
            horizontalInput = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if(verticalInput < maxSpeed)
        {
            verticalInput += acceleration;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if(verticalInput > -maxSpeed)
        {
            verticalInput -= acceleration;
        }
    }
    else
    {
        if(verticalInput > 0)
        {
            verticalInput -= acceleration;
        }
        else if(verticalInput < 0)
        {
            verticalInput += acceleration;
        }
    }
    if(verticalInput < acceleration && verticalInput > -acceleration)
    {
        verticalInput = 0;
    }
    if(horizontalInput < acceleration && horizontalInput > -acceleration)
    {
        horizontalInput = 0;
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