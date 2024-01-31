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



float easeIn;
float maxSpeed = 1.0f;
//want to add lerp maybe a custom function
void GLCCamera::processInput(GLFWwindow *window, float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 3 * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if(easeIn >= maxSpeed)
        {
            easeIn = easeIn;
        }
        else
        {
            easeIn += 1.1f * deltaTime;
            std::cout << easeIn;
        }
        cameraPos += cameraSpeed * glm::vec3(easeIn, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS &&
    glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS &&
    glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS &&
    glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS)
    {
        easeIn = 0.0f;
    }
}