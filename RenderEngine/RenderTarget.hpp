#pragma once

class RenderTarget
{
  private:
    unsigned int multisampledColorRenderBuffer;
    unsigned int multisampledDepthRenderBuffer;
    unsigned int multisampledFbo;
    const unsigned int samples = 8;

    /* Single-sampled FBO objects */
    unsigned int colorTexture;
    unsigned int fbo;
    unsigned int m_Width;
    unsigned int m_Height;
    void Generate();

  public:
    RenderTarget(unsigned int p_X, unsigned int p_Y);
    ~RenderTarget();
    void Use();
    void UnUse();
    void Resize(unsigned int p_X, unsigned int p_Y);
    unsigned int GetTexture();
};
