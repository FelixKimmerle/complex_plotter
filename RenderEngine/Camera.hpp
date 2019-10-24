#pragma once
#include <glm/glm.hpp>
#include <SFML/System.hpp>

class Camera
{
private:
    sf::Clock clock;    
public:
    Camera(/* args */);
    ~Camera();
    void Update();
    glm::vec3 position;
    glm::vec3 rotation;
};
