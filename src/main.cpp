#include <GLC.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>


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

    GLCCamera MainCamera(GLC.window);
    MainCamera.projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    GLCShader defaultShader("shaders/default.vert", "shaders/default.frag");

    VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));

	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 0, (void*)0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


    while(!glfwWindowShouldClose(GLC.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        MainCamera.processInput(GLC.window, deltaTime);


        GLC.processInput();

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        defaultShader.Use();
        VAO1.Bind();

        view = MainCamera.view();
        projection = MainCamera.projection;
        model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));


        int modelLoc = glGetUniformLocation(defaultShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(defaultShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(defaultShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}