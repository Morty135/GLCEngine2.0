#include <GLC.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>


int width = 1280;
int height = 800;

vertex vertices[] = {
    vertex{glm::vec3(0.5f,  0.5f, 0.0f)},  // top right
    vertex{glm::vec3( 0.5f, -0.5f, 0.0f)},  // bottom right
    vertex{glm::vec3(-0.5f, -0.5f, 0.0f)},  // bottom left
    vertex{glm::vec3(-0.5f,  0.5f, 0.0f)}   // top left 
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
    GLCShader defaultShader("../shaders/default.vert", "../shaders/default.frag");

    std::vector <vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));

    GLCMesh Plane(verts, ind);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(GLC.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        MainCamera.processInput(GLC.window, deltaTime);


        GLC.processInput();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        defaultShader.Use();

        Plane.Draw(defaultShader, MainCamera);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}