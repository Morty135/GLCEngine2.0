#include <GLCTerrain.h>

GLCTerrain::GLCTerrain()
    : TerrainMesh(vertices, indices, textures, 1)
{

    //GLCMesh(std::vector <vertex>& vertices, std::vector <unsigned int>& indices, std::vector <GLCTextureStruct>& textures, unsigned int instances);
    vertices.clear();
    indices.clear();

    int gridSize = 100;
    float cellSize = 0.5;



    // Generate vertices
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            float x = j * cellSize;
            float z = i * cellSize;
            vertices.push_back(vertex{
                glm::vec3(x, -7.0f, z),
                glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec2((float)j / gridSize, (float)i / gridSize)
            });
        }
    }

    // Generate indices
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int topLeft = i * (gridSize + 1) + j;
            int topRight = topLeft + 1;
            int bottomLeft = topLeft + (gridSize + 1);
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }
}





void GLCTerrain::Draw(GLCShader& shader, GLCCamera& camera)
{
    TerrainMesh.Draw(shader, camera);
}



void GLCTerrain::Delete()
{
	TerrainMesh.Delete();
}