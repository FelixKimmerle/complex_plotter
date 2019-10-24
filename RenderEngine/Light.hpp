#pragma once
#include <glm/glm.hpp>

class Light
{
  private:
    /* data */
  public:
    Light(glm::vec3 p_position, glm::vec3 p_color);
    ~Light();
    glm::vec3 position;
    glm::vec3 color;
};
