#pragma once
#include <SFML/Graphics.hpp>

class DisplayManager
{
private:
  sf::RenderWindow m_Window;
  sf::Vector2f m_Rotation;
  sf::Vector2f m_Last;
  bool m_bClick;
  unsigned int m_uiZoom;
  sf::Clock m_Clock;

public:
  DisplayManager();
  ~DisplayManager();
  void create();
  void update();
  bool isOpen();
  float GetAspectRatio() const;
  sf::Vector2f GetRotation();
  unsigned int GetZoom();
};
