#include <GLCMesh.h>

GLCMesh::GLCMesh(std::vector <vertex>& vertices, std::vector <unsigned int>& indices)
{
    GLCMesh::vertices = vertices;
    GLCMesh::indices = indices;



    VAO.Bind();

	VBO VBO(vertices);

	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 0, (void*)0);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

}





void GLCMesh::Draw(GLCShader& shader, GLCCamera& camera)
{
    shader.Use();
    VAO.Bind();
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.view();
    glm::mat4 projection = camera.projection;

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
