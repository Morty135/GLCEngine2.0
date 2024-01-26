#include <GLC.h>
#include <VAO.h>


int width = 800;
int height = 600;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

int main()
{
    GLC GLC(width, height);

    GLCShader defaultShader("shaders/default.vert", "shaders/default.frag");

    unsigned int VBO, EBO;
    
    VAO VAO1;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    VAO1.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

    while(!glfwWindowShouldClose(GLC.window))
    {
        GLC.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader.Use();
        VAO1.Bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }

    VAO1.Delete();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}