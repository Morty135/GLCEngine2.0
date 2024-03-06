#include <GLC.h>


int width = 1280;
int height = 800;

float size = 4.0f;
float textureRepeat = 4.0f; 

vertex vertices[] = {
    vertex{glm::vec3(-1.0f, 1.0f,  0.0f) * size , glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) * textureRepeat},
	vertex{glm::vec3(-1.0f, -1.0f, 0.0f) * size , glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) * textureRepeat},
	vertex{glm::vec3( 1.0f, -1.0f, 0.0f) * size , glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) * textureRepeat},
	vertex{glm::vec3( 1.0f, 1.0f,  0.0f) * size , glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) * textureRepeat}
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

    GLCTexture textures[]
	{
		GLCTexture((ParentDir + "/resources/plankTexture/planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		GLCTexture((ParentDir + "/resources/plankTexture/planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};


    std::vector <vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <GLCTexture> tex(textures, textures + sizeof(textures) / sizeof(GLCTexture));

    GLCMesh Plane(verts, ind, tex);

    GLCModel Character((ParentDir + "/resources/character/character.obj").c_str());

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

        //Plane.Draw(defaultShader, MainCamera);
        Character.Draw(defaultShader, MainCamera);

        glfwSwapBuffers(GLC.window);
        glfwPollEvents();
    }
    defaultShader.Delete();

    glfwTerminate();
    return 0;
}