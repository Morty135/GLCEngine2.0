#include <GLC.h>


int width = 1280;
int height = 800;

int fbWidth = 320;
int fbHeight = 200;

std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

int main()
{
    GLC GLC(width, height);

    GLCInput GLCInput(GLC.window);

    GLCCamera MainCamera(GLC.window);

    MainCamera.projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 200.0f);
    //MainCamera.projection = glm::ortho(-8.0f, 8.0f, -6.0f, 6.0f, 0.1f, 100.0f);
    //camera pos adjustment
    MainCamera.position += glm::vec3(0.0f, 45.0f, 37.0f);

    glViewport(0, 0, width, height);

    GLCShader defaultShader((ParentDir + "/shaders/default.vert").c_str(), (ParentDir + "/shaders/default.frag").c_str());

    GLCShader terrainShader((ParentDir + "/shaders/terrain.vert").c_str(), (ParentDir + "/shaders/terrain.frag").c_str());

    GLCFramebuffer framebuffer(fbWidth, fbHeight, width, height);

    glEnable(GL_DEPTH_TEST);



    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());
    //Transform does not need to be set for the object to exist the default matrix is 1.0f
    Character.Transform = glm::rotate(Character.Transform, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    //this demonstrates scaling on transfform mat
    Character.Transform = glm::scale(Character.Transform, glm::vec3(1.0f, 1.0f, 1.0f));



    GLCTerrain Terrain(50, 1, 0.005);





    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    auto FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer is not complete: " << FBOStatus << std::endl;

    while(!glfwWindowShouldClose(GLC.window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        MainCamera.position = glm::vec3(Character.Transform[3]) + glm::vec3(0.0f, 20.0f, 20.0f);

        GLCInput.processInput();

        framebuffer.Bind();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        Character.Draw(defaultShader, MainCamera);
        Character.Transform = glm::translate(Character.Transform, -GLCInput.Combined() * deltaTime);
        //Character.Transform = glm::rotate(Character.Transform, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));


        Terrain.Draw(terrainShader ,MainCamera, Character.Transform);

        framebuffer.Use();

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }



    Character.Delete();
    defaultShader.Delete();
    framebuffer.Delete();
    Terrain.Delete();



    glfwTerminate();
    return 0;
}