#include <GLC.h>


int width = 1280;
int height = 800;

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

    GLCShader defaultShader((ParentDir + "/shaders/default.vert").c_str(), (ParentDir + "/shaders/default.frag").c_str());

    GLCShader grassShader((ParentDir + "/shaders/grass.vert").c_str(), (ParentDir + "/shaders/grass.frag").c_str());

    GLCShader terrainShader((ParentDir + "/shaders/terrain.vert").c_str(), (ParentDir + "/shaders/terrain.frag").c_str());



    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());
    //Transform does not need to be set for the object to exist the default matrix is 1.0f
    Character.Transform = glm::rotate(Character.Transform, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));

    



    GLCTerrain Terrain(50, 1, 0.005);





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


        Character.Draw(defaultShader, MainCamera);
        Character.Transform = glm::translate(Character.Transform, -GLCInput.Combined() * deltaTime);
        //Character.Transform = glm::rotate(Character.Transform, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));


        Terrain.Draw(terrainShader, grassShader ,MainCamera, Character.Transform);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }



    Character.Delete();
    defaultShader.Delete();
    Terrain.Delete();



    glfwTerminate();
    return 0;
}