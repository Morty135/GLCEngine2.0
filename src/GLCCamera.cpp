#include <GLCCamera.h>



glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);



float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  45.0f;



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



GLCCamera::GLCCamera(GLFWwindow* window)
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}





glm::mat4 GLCCamera::view()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
}



float InterpolateXUp;
float InterpolateXDown;
float InterpolateYLeft;
float InterpolateYRight;
float maxValue = 1.0f;
float InterpolationSpeed = 3.5f;
//want to add lerp maybe a custom function
void GLCCamera::processInput(GLFWwindow *window, float deltaTime)
{
    const float cameraSpeed = 2 * deltaTime;



    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
        if(InterpolateXUp >= maxValue)
        {
            InterpolateXUp = InterpolateXUp;
        }
        else
        {
            InterpolateXUp += InterpolationSpeed * deltaTime;
        }
        cameraPos += cameraSpeed * glm::vec3(0.0f, InterpolateXUp, 0.0f);
    }
    else
    {
        if(InterpolateXUp <= 0.0f)
        {
            InterpolateXUp = InterpolateXUp;
        }
        else
        {
            InterpolateXUp -= InterpolationSpeed * deltaTime;
        }
        cameraPos += cameraSpeed * glm::vec3(0.0f, InterpolateXUp, 0.0f);
    }



    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if(InterpolateXDown >= maxValue)
        {
            InterpolateXDown = InterpolateXDown;
        }
        else
        {
            InterpolateXDown += InterpolationSpeed * deltaTime;
        }
        cameraPos -= cameraSpeed * glm::vec3(0.0f, InterpolateXDown, 0.0f);
    }
    else
    {
        if(InterpolateXDown <= 0.0f)
        {
            InterpolateXDown = InterpolateXDown;
        }
        else
        {
            InterpolateXDown -= InterpolationSpeed * deltaTime;
        }
        cameraPos -= cameraSpeed * glm::vec3(0.0f, InterpolateXDown, 0.0f);
    }



    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if(InterpolateYLeft >= maxValue)
        {
            InterpolateYLeft = InterpolateYLeft;
        }
        else
        {
            InterpolateYLeft += InterpolationSpeed * deltaTime;
        }
        cameraPos -= cameraSpeed * glm::vec3(InterpolateYLeft, 0.0f, 0.0f);
    }
    else
    {
        if(InterpolateYLeft <= 0.0f)
        {
            InterpolateYRight = InterpolateYRight;
        }
        else
        {
            InterpolateYLeft -= InterpolationSpeed * deltaTime;
        }
        cameraPos -= cameraSpeed * glm::vec3(InterpolateYLeft, 0.0f, 0.0f);
    }



    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if(InterpolateYRight >= maxValue)
        {
            InterpolateYRight = InterpolateYRight;
        }
        else
        {
            InterpolateYRight += InterpolationSpeed * deltaTime;
        }
        cameraPos += cameraSpeed * glm::vec3(InterpolateYRight, 0.0f, 0.0f);
    }
    else
    {
        if(InterpolateYRight <= 0.0f)
        {
            InterpolateYRight = InterpolateYRight;
        }
        else
        {
            InterpolateYRight -= InterpolationSpeed * deltaTime;
        }
        cameraPos += cameraSpeed * glm::vec3(InterpolateYRight, 0.0f, 0.0f);
    }
}