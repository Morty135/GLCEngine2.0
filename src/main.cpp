#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <GLC.h>


int width = 800;
int height = 600;



int main()
{
    GLC GLC(width, height);

    while(!glfwWindowShouldClose(GLC.window))
    {
        GLC.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }



    glfwTerminate();
    return 0;
}