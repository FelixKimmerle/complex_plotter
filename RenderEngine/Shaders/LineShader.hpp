#pragma once
#include "ShaderProgram.hpp"
#include <RenderEngine/Camera.hpp>
#include <RenderEngine/Light.hpp>

class LineShader : public ShaderProgram
{
private:
    /* data */
public:
    LineShader(/* args */);
    virtual ~LineShader();
    virtual void BindAttributes();
    virtual void LoadAllUniformLocations();
    void LoadTransformationMatrix(const glm::mat4 &mat) const;
    void LoadProjectionMatrix(const glm::mat4 &mat) const;
    void LoadViewMatrix(const Camera &camer) const;

  protected:
};
