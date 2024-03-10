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
    //camera pos adjustment
    MainCamera.position += glm::vec3(0.0f, 7.0f,10.0f);

    GLCShader defaultShader((ParentDir + "/shaders/default.vert").c_str(), (ParentDir + "/shaders/default.frag").c_str());



    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());
    //Transform does not need to be set for the object to exist the default matrix is 1.0f
    //Character.Transform = glm::rotate(Character.Transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 0.0));



    GLCModel Floor((ParentDir + "/resources/Floor/Floor.obj").c_str());
    Floor.Transform = glm::translate(Floor.Transform, glm::vec3(0.0, -7.0, -7.0));
    Floor.Transform = glm::scale(Floor.Transform, glm::vec3(10.0, 1.0, 10.0));  

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
        //Character.Transform = glm::rotate(Character.Transform, glm::radians(1.0f), glm::vec3(0.0, 0.0, 1.0));

        Floor.Draw(defaultShader, MainCamera);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}