#include "LineShader.hpp"
#include <iostream>
#include <RenderEngine/Maths.hpp>

LineShader::LineShader(/* args */)
{
    LoadFiles("RenderEngine/Shaders/basic");
}

LineShader::~LineShader()
{
}

void LineShader::BindAttributes()
{
    std::cout << "BIND" << std::endl;
    BindAttribute(0, "position");
    BindAttribute(1, "color");
    //BindAttribute(1, "textureCoords");
}

void LineShader::LoadAllUniformLocations()
{
    LoadUniformVariable("transformationMatrix");
    LoadUniformVariable("projectionMatrix");
    LoadUniformVariable("viewMatrix");
}
void LineShader::LoadTransformationMatrix(const glm::mat4 &mat)const
{
    LoadMatrix4(GetUniformLocation("transformationMatrix"), mat);
}

void LineShader::LoadProjectionMatrix(const glm::mat4 &mat) const
{
    LoadMatrix4(GetUniformLocation("projectionMatrix"), mat);
}

void LineShader::LoadViewMatrix(const Camera &camera) const
{
    LoadMatrix4(GetUniformLocation("viewMatrix"), crateViewMatrix(camera));
}
