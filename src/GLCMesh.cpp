#include <GLCMesh.h>

GLCMesh::GLCMesh(std::vector <vertex>& vertices, std::vector <unsigned int>& indices, std::vector <GLCTextureStruct>& textures)
{
    GLCMesh::vertices = vertices;
    GLCMesh::indices = indices;
    GLCMesh::textures = textures;


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





void GLCMesh::Draw(GLCShader& shader, GLCCamera& camera, unsigned int instances)
{
    shader.Use();
    VAO.Bind();

	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;
		if(name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if(name == "texture_specular")
			number = std::to_string(specularNr++);

		glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
    
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

	if(instances > 1)
	{
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
		/*
		for(unsigned int i = 0; i < instances; i++)
		{
			int projectionLoc = glGetUniformLocation(shader.ID, "offsets[" + std::to_string(i) + "]");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		}  
		*/
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instances);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}



void GLCMesh::Delete()
{
	VAO.Delete();
}