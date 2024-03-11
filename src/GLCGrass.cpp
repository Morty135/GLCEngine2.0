#include <GLCGrass.h>

GLCGrass::GLCGrass(std::vector <vertex>& vertices, std::vector <unsigned int>& indices)
{
    GLCGrass::vertices = vertices;
    GLCGrass::indices = indices;



    int index = 0;
    float offset = 0.1f;
    for(int y = -10; y < 10; y += 2)
    {
        for(int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }  



    VAO.Bind();

	VBO VBO(vertices);

	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(vertex), (void*)(6 * sizeof(float)));


	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

}





void GLCGrass::Draw(GLCShader& shader, GLCCamera& camera)
{
    shader.Use();
    VAO.Bind();

    
    glm::mat4 model = glm::mat4(1.0f);
	model = Transform;
    glm::mat4 view = camera.view();
    glm::mat4 projection = camera.projection;



    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    for(unsigned int i = 0; i < amount; i++)
    {
        std::string iString = std::to_string(i);
        std::string uniformName = "offsets[" + iString + "]";
        int OffsetsLoc = glGetUniformLocation(shader.ID, uniformName.c_str());
        glUniformMatrix4fv(OffsetsLoc, 1, GL_FALSE, glm::value_ptr(translations[i]));
    }  



    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, amount);
}



void GLCGrass::Delete()
{
	VAO.Delete();
}