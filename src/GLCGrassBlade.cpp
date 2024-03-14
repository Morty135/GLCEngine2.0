#include <GLCGrassBlade.h>
#include <GLCMesh.h>

GLCGrassBlade::GLCGrassBlade(unsigned int instances)
{
    GLCGrassBlade::instances = instances;
    GLCMesh::vertices = {
    // Positions          Normals         Texture Coordinates
        {glm::vec3(0.0, -0.24, 0.73), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0)}, // Bottom left
        {glm::vec3(0.0, -2.7, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0.0)},  // Bottom right
        {glm::vec3(0.0, -0.24, -0.73), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 1.0)}, // Top left
        {glm::vec3(0.0, -2.7, -1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)},   // Top right
        {glm::vec3(0.0, 1.72, 0.49), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)},   // Top right
        {glm::vec3(0.0, 1.72, -0.49), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)},   // Top right
        {glm::vec3(0.0, 3.5, 0.18), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)},   // Top right
        {glm::vec3(0.0, 3.5, -0.18), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)}   // Top right
    };
    GLCGrassBlade::indices = 
    {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };


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





void GLCGrassBlade::Draw(GLCShader& shader, GLCCamera& camera)
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

	glm::vec2 translations[instances];
		int index = 0;
		float offset = 0.1f;
		int gridSize = sqrt(instances); 
		for(int y = -gridSize; y < gridSize; y += 2)
		{
			for(int x = -gridSize; x < gridSize; x += 2)
			{
				glm::vec2 translation;
				translation.x = static_cast<float>(x) / static_cast<float>(gridSize) + offset;
				translation.y = static_cast<float>(y) / static_cast<float>(gridSize) + offset;
				translations[index++] = translation;
			}
		}

		for(unsigned int i = 0; i < instances; i++)
		{
			int projectionLoc = glGetUniformLocation(shader.ID,  ("offsets[" + std::to_string(i) + "]").c_str());
			glUniform2fv(projectionLoc, 1, glm::value_ptr(translations[i]));
		}  
		
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instances);
}



void GLCGrassBlade::Delete()
{
	VAO.Delete();
}