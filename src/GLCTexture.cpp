#include <GLCTexture.h>

GLCTexture::GLCTexture(const char* textureSource, const char* texType, unsigned int slot, GLenum format, GLenum pixelType)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(textureSource, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, pixelType, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void GLCTexture::texUnit(GLCShader& shader, const char* uniform, unsigned int unit)
{
	// Gets the location of the uniform
	unsigned int texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Use();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void GLCTexture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GLCTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GLCTexture::Delete()
{
	glDeleteTextures(1, &ID);
}