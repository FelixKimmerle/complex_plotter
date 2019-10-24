#include "TerrainShader.hpp"
#include "../Maths.hpp"

TerrainShader::TerrainShader()
{
    LoadFiles("RenderEngine/Shaders/terrain");
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::LoadTransformMatrix(const glm::mat4 &matrix)
{
    LoadMatrix4(GetUniformLocation("transformMatrix"), matrix);
}

void TerrainShader::LoadProjectionMatrix(const glm::mat4 &matrix)
{
    LoadMatrix4(GetUniformLocation("projectionMatrix"), matrix);
}

void TerrainShader::LoadViewMatrix(const glm::mat4 &cameraViewMatrix)
{
    LoadMatrix4(GetUniformLocation("viewMatrix"), cameraViewMatrix);
}

void TerrainShader::LoadLight(const Light &light, float ambientLight)
{
    LoadVector(GetUniformLocation("lightPosition"), light.position);
    LoadVector(GetUniformLocation("lightColor"), light.color);
    LoadFloat(GetUniformLocation("ambientLight"), ambientLight);
}

void TerrainShader::LoadShineVariables(float shineDamper, float shine)
{
    LoadFloat(GetUniformLocation("shineDamper"), shineDamper);
    LoadFloat(GetUniformLocation("shine"), shine);
}

void TerrainShader::BindAttributes()
{
    BindAttribute(0, "position");
    BindAttribute(1, "normal");
}

void TerrainShader::LoadAllUniformLocations()
{

    /*location_TransformMatrix = GetUniformLocation("transformMatrix");
	location_ProjectionMatrix = GetUniformLocation("projectionMatrix");
	location_ViewMatrix = GetUniformLocation("viewMatrix");
	location_lightPosition = GetUniformLocation("lightPosition");
	location_lightColor = GetUniformLocation("lightColor");
	location_ambientLight = GetUniformLocation("ambientLight");
	location_shineDamper = GetUniformLocation("shineDamper");
	location_shine = GetUniformLocation("shine");
    */
    LoadUniformVariable("transformMatrix");
    LoadUniformVariable("projectionMatrix");
    LoadUniformVariable("viewMatrix");
    LoadUniformVariable("lightPosition");
    LoadUniformVariable("lightColor");
    LoadUniformVariable("ambientLight");
    LoadUniformVariable("shineDamper");
    LoadUniformVariable("shine");
}