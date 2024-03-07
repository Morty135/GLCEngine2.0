#include <GLCModel.h>
#include <stb_image.h>


void GLCModel::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}



void GLCModel::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}



GLCMesh GLCModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<GLCTexture> textures;



    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        vertex vertex;
        glm::vec3 vector; 
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;  

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texture = vec;
        }
        else
        {
            vertex.texture = glm::vec2(0.0f, 0.0f);  
        }

        vertices.push_back(vertex);
    }



    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  


    //textures here

    return GLCMesh(vertices, indices, textures);
}





/*
GLCTexture textures[]
{
    GLCTexture((ParentDir + "/resources/plankTexture/planks.png").c_str(), "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
    GLCTexture((ParentDir + "/resources/plankTexture/planksSpec.png").c_str(), "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
};
*/



void GLCModel::Draw(GLCShader &shader,GLCCamera& camera)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader, camera);
}  