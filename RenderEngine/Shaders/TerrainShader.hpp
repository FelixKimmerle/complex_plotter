#pragma once

#include "ShaderProgram.hpp"
#include "../Camera.hpp"
#include "../Light.hpp"

class TerrainShader : public ShaderProgram
{
  public:
    TerrainShader();
    virtual ~TerrainShader();
    virtual void BindAttributes();
    virtual void LoadAllUniformLocations();
    void LoadTransformMatrix(const glm::mat4 &matrix);
    void LoadProjectionMatrix(const glm::mat4 &matrix);
    void LoadViewMatrix(const glm::mat4 &cameraViewMatrix);
    void LoadLight(const Light &light, float ambientLight);
    void LoadShineVariables(float shineDamper, float shine);
};