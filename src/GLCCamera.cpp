#include <GLCCamera.h>



glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);



float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  -40.0f;



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
    return glm::lookAt(position, position + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
}