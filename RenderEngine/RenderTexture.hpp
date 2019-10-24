#pragma once
#include <GL/glew.h>

class RenderTexture
{
  private:
    unsigned int depthrenderbuffer;
    GLuint FramebufferName;
    GLenum DrawBuffers[1];

  public:
    void bind();
    void unbind();
    RenderTexture(unsigned int pwidth, unsigned int pheight);
    ~RenderTexture();
    unsigned int renderedTexture;
    unsigned int width;
    unsigned int height;
};
