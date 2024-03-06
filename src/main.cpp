#include <GLC.h>


int width = 1280;
int height = 800;

std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

int main()
{
    GLC GLC(width, height);

    GLCInput GLCInput(GLC.window);

    GLCCamera MainCamera(GLC.window);

    MainCamera.projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    //MainCamera.projection = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, 0.1f, 100.0f);

    GLCShader defaultShader((ParentDir + "/shaders/default.vert").c_str(), (ParentDir + "/shaders/default.frag").c_str());

    GLCTexture textures[]
	{
		GLCTexture((ParentDir + "/resources/plankTexture/planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		GLCTexture((ParentDir + "/resources/plankTexture/planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    //camera pos adjustment
    MainCamera.position += glm::vec3(0.0f,-7.0f,10.0f);

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

        Character.Draw(defaultShader, MainCamera);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}