#include <GLC.h>


int width = 1280;
int height = 800;

vertex vertices[] = {
    vertex{glm::vec3(-1.0f, 1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.7f, 0.2f), glm::vec2(0.0f, 0.0f)},
	vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.2f, 0.7f), glm::vec2(0.0f, 1.0f)},
	vertex{glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.7f, 1.0f), glm::vec2(1.0f, 1.0f)},
	vertex{glm::vec3( 1.0f, 1.0f,  0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.7f, 0.2f, 1.0f), glm::vec2(1.0f, 0.0f)}
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,
	0, 2, 3
};

std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

int main()
{
    GLC GLC(width, height);

    GLCInput GLCInput(GLC.window);

    GLCCamera MainCamera(GLC.window);

    MainCamera.projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

    GLCShader defaultShader((ParentDir + "/shaders/default.vert").c_str(), (ParentDir + "/shaders/default.frag").c_str());

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

        MainCamera.position += GLCInput.Combined() * deltaTime;

        GLCInput.processInput();

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