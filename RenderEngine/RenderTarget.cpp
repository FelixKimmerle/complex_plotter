#include "RenderTarget.hpp"
#include <GL/glew.h>
#include <iostream>
RenderTarget::RenderTarget(unsigned int p_X, unsigned int p_Y) : m_Width(p_X), m_Height(p_Y)
{
    Generate();
}

void RenderTarget::Generate()
{
    glGenRenderbuffers(1, &multisampledColorRenderBuffer);
    glGenRenderbuffers(1, &multisampledDepthRenderBuffer);
    glGenFramebuffers(1, &multisampledFbo);

    glBindFramebuffer(GL_FRAMEBUFFER, multisampledFbo);
    glBindRenderbuffer(GL_RENDERBUFFER, multisampledColorRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGB, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, multisampledColorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, multisampledDepthRenderBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, multisampledDepthRenderBuffer);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenTextures(1, &colorTexture);
    glGenFramebuffers(1, &fbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // we also want to sample this texture later
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // we also want to sample this texture later
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTarget::~RenderTarget()
{
    glDeleteRenderbuffers(1,&multisampledColorRenderBuffer);
    glDeleteRenderbuffers(1,&multisampledDepthRenderBuffer);
    glDeleteFramebuffers(1,&multisampledFbo);
    glDeleteFramebuffers(1,&fbo);
    glDeleteTextures(1,&colorTexture);
}

void RenderTarget::Use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, multisampledFbo);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_Width, m_Height);
}
void RenderTarget::UnUse()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void RenderTarget::Resize(unsigned int p_X, unsigned int p_Y)
{
    if (p_X != m_Width || p_Y != m_Height)
    {
        m_Width = p_X;
        m_Height = p_Y;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteRenderbuffers(1,&multisampledColorRenderBuffer);
        glDeleteRenderbuffers(1,&multisampledDepthRenderBuffer);
        glDeleteFramebuffers(1,&multisampledFbo);
        glDeleteFramebuffers(1,&fbo);
        glDeleteTextures(1,&colorTexture);

        Generate();
    }
}

unsigned int RenderTarget::GetTexture()
{
    return colorTexture;
}