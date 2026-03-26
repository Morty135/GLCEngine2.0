#include "GLCFramebuffer.h"

GLCFramebuffer::GLCFramebuffer(int width, int height, int screenWidth, int screenHeight)
:   width(width),
    height(height),
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    framebufferProgram(
        (ParentDir + "/shaders/framebuffer.vert").c_str(),
        (ParentDir + "/shaders/framebuffer.frag").c_str()
    )
{
    this->width = width;
    this->height = height;

    framebufferProgram.Use();
	glUniform1i(glGetUniformLocation(framebufferProgram.ID, "screenTexture"), 0);

	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    auto FBOStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer is not complete: " << FBOStatus << std::endl;
}



void GLCFramebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glViewport(0, 0, width, height);
}



void GLCFramebuffer::Use()
{
    framebufferProgram.Use();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screenWidth, screenHeight);
    glBindVertexArray(rectVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}



void GLCFramebuffer::Delete()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &framebufferTexture);
    glDeleteRenderbuffers(1, &RBO);
    framebufferProgram.Delete();
}