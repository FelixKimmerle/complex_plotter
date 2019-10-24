#include "Line.hpp"

Line::Line(RawModel p_model, glm::vec3 p_position, glm::vec3 p_rotation, float p_scale) : model(p_model), position(p_position), rotation(p_rotation), scale(p_scale)
{
}

Line::~Line()
{
}

void Line::Move(const glm::vec3 offset)
{
    position += offset;
}
void Line::Rotate(const glm::vec3 offset)
{
    rotation += offset;
}