#include <GLC.h>


int width = 1280;
int height = 800;

std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();

float rectangleVertices[] =
{
	// Coords    // texCoords
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

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

    GLCShader framebufferProgram((ParentDir + "/shaders/framebuffer.vert").c_str(), (ParentDir + "/shaders/framebuffer.frag").c_str());
    framebufferProgram.Use();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);

    GLCShader terrainShader((ParentDir + "/shaders/terrain.vert").c_str(), (ParentDir + "/shaders/terrain.frag").c_str());

    glEnable(GL_DEPTH_TEST);



    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());
    //Transform does not need to be set for the object to exist the default matrix is 1.0f
    Character.Transform = glm::rotate(Character.Transform, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    //this demonstrates scaling on transfform mat
    Character.Transform = glm::scale(Character.Transform, glm::vec3(1.0f, 1.0f, 1.0f));



    GLCTerrain Terrain(50, 1, 0.005);





    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));



    unsigned int FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    unsigned int framebufferTexture;
    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    unsigned int RBO;
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

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

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);


        Character.Draw(defaultShader, MainCamera);
        Character.Transform = glm::translate(Character.Transform, -GLCInput.Combined() * deltaTime);
        //Character.Transform = glm::rotate(Character.Transform, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));


        Terrain.Draw(terrainShader ,MainCamera, Character.Transform);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindVertexArray(rectVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }



    Character.Delete();
    defaultShader.Delete();
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &framebufferTexture);
    glDeleteRenderbuffers(1, &RBO);
    Terrain.Delete();



    glfwTerminate();
    return 0;
}