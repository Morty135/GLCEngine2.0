#include <GLCTerrain.h>





GLCTerrain::GLCTerrain(int gridSize, float cellSize, float frequency)
{
    GLCTerrain::gridSize = gridSize;
    GLCTerrain::cellSize = cellSize;
    GLCTerrain::frequency = frequency;

    GLCChunk chunk(gridSize, cellSize, frequency, 0, 0);
    chunks.push_back(chunk);
}





void GLCTerrain::Draw(GLCShader& GroundShader, GLCShader& GrassShader, GLCCamera& camera, glm::mat4& playerTransform)
{
    glm::vec3 playerPosition(playerTransform[3][0], 0.0f, playerTransform[3][2]);



    int X = std::round(playerPosition.x / (gridSize * cellSize));
    int Z = std::round(playerPosition.z / (gridSize * cellSize));



    int startX = X - 2;
    int endX = X + 2;
    int startZ = Z - 2;
    int endZ = Z + 2;

    // Iterate over the sectors surrounding the player
    for (int x = startX; x <= endX; x++)
    {
        for (int z = startZ; z <= endZ; z++)
        {
            // Check if a chunk already exists for the current sector
            bool chunkExists = false;
            for (unsigned int i = 0; i < chunks.size(); i++)
            {
                if (x * gridSize == chunks[i].xOffset && z * gridSize == chunks[i].zOffset)
                {
                    chunkExists = true;
                    break;
                }
            }
            
            // If no chunk exists for the current sector, create a new chunk
            if (!chunkExists)
            {
                GLCChunk chunk(gridSize, cellSize, frequency, x, z);
                chunks.push_back(chunk);
            }
        }
    }

    prevX = X;
    prevZ = Z;

    for(unsigned int i = 0; i < chunks.size(); i++)
    {
        chunks[i].Draw(GroundShader, GrassShader, camera);
    }
}





void GLCTerrain::Delete()
{
    for(unsigned int i = 0; i < chunks.size(); i++)
    {
        chunks[i].Delete();
    }
}