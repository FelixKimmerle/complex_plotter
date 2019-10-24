#pragma once
#include "RawModel.hpp"
#include <glm/glm.hpp>

class Line
{
private:
    /* data */
public:
    Line(RawModel model,glm::vec3 position,glm::vec3 rotation, float scale);
    Line() : model(0,0){};
    ~Line();
    void Move(const glm::vec3 offset);
    void Rotate(const glm::vec3 offset);
    RawModel model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
};
