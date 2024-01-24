#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <applicationManager.h>


int width = 800;
int height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    applicationManager applicationManager(width, height);

    while(!glfwWindowShouldClose(applicationManager.window))
    {
        applicationManager.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(applicationManager.window);
        glfwPollEvents();
    }



    glfwTerminate();
    return 0;
}