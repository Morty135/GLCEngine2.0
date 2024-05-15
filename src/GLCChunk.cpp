#include <GLCChunk.h>

GLCChunk::GLCChunk() : ChunkMesh(GenerateMesh()) 
{

}





void GLCChunk::Draw(GLCShader& shader, GLCCamera& camera)
{
    ChunkMesh.Draw(shader, camera);
}



void GLCChunk::Delete()
{
	ChunkMesh.Delete();
}

GLCMesh GLCChunk::GenerateMesh()
{
    vertices.clear();
    indices.clear();



    siv::PerlinNoise perlinFunc{ std::random_device{} };


    // Generate vertices
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            double x = j * cellSize;
            double z = i * cellSize;

            double perlinHeight = perlinFunc.octave2D_01(x * frequency, z * frequency, 7, 0.5);

            vertices.push_back(vertex{
                glm::vec3(x, -9.0 + perlinHeight * 10, z),
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec2(perlinHeight, 0.0f)
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
    return GLCMesh(vertices, indices, textures, 1);
}