#include "Camera.hpp"
#include <SFML/Window.hpp>

Camera::Camera(/* args */) : position(0), rotation(0)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
    float delta = clock.restart().asSeconds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        position.z -= 100*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        position.z += 100*delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        rotation.y += 100*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        rotation.y -= 100*delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        position.x -= 100*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        position.x += 100*delta;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        position.y += 100*delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        position.y -= 100*delta;
    }
}
