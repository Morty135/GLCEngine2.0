#include <GLCChunk.h>

GLCChunk::GLCChunk(int gridSize, float cellSize, float frequency, int X, int Y) : ChunkMesh(GenerateMesh()), Grass(GenerateGrass())
{
    GLCChunk::gridSize = gridSize;
    GLCChunk::cellSize = cellSize;
    GLCChunk::frequency = frequency;

    GLCChunk::xOffset = X * gridSize;
    GLCChunk::zOffset = Y * gridSize;

    ChunkMesh = GenerateMesh();
    Grass = GenerateGrass();
}





void GLCChunk::Draw(GLCShader& GroundShader, GLCShader& GrassShader, GLCCamera& camera)
{
    ChunkMesh.Draw(GroundShader, camera);
    Grass.Draw(GrassShader, camera);
}





void GLCChunk::Delete()
{
	ChunkMesh.Delete();
    Grass.Delete();
}





GLCMesh GLCChunk::GenerateMesh()
{
    vertices.clear();
    indices.clear();



    // Generate vertices
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            double x = (j + xOffset) * cellSize;
            double z = (i + zOffset) * cellSize;

            double perlinHeight = perlinFunc.octave2D_01(x * frequency, z * frequency, 5, 0.5);

            vertices.push_back(vertex{
                glm::vec3(x, -19.0 + perlinHeight * 40, z),
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
    std::vector<glm::vec3> instaceOffsets = { glm::vec3(0.0f) };
    return GLCMesh(vertices, indices, textures, instaceOffsets);
}



GLCModel GLCChunk::GenerateGrass()
{
    for(int i = 0; i < 4000; i++)
    {
        instaceOffsets.push_back(glm::vec3(i, i, i));
    }
    std::string ParentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
    return GLCModel((ParentDir + "/resources/GrassBlade/GrassBlade.obj").c_str(), instaceOffsets);
}

