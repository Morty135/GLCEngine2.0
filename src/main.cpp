#include <GLC.h>


int width = 800;
int height = 600;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

int main()
{
    GLC GLC(width, height);

    GLCShader defaultShader("shaders/default.vert", "shaders/default.frag");

    VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));

    while(!glfwWindowShouldClose(GLC.window))
    {
        GLC.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader.Use();
        glBindVertexArray(VAO1.ID);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }

    VAO1.Delete;
    glDeleteBuffers(1, &VBO);
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}