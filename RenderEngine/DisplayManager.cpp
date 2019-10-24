#include <GL/glew.h>
#include "DisplayManager.hpp"
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <Imgui/imgui-SFML.h>
#include <Imgui/imgui.h>
#define WIDTH 1280
#define HEIGHT 720

DisplayManager::DisplayManager()
{
    m_bClick = false;
    m_uiZoom = 500;
}

DisplayManager::~DisplayManager()
{
}

void DisplayManager::create()
{

    sf::ContextSettings settingsx(24, 8, 8);
    m_Window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "OpenGL", sf::Style::Default, settingsx);
    m_Window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(m_Window);
    m_Clock.restart();
    ImGui::SFML::Update(m_Window, m_Clock.restart());

    sf::ContextSettings settings = m_Window.getSettings();

    std::cout << "depth bits: " << settings.depthBits << std::endl;
    std::cout << "stencil bits: " << settings.stencilBits << std::endl;
    std::cout << "antialiasing level: " << settings.antialiasingLevel << std::endl;
    std::cout << "version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, WIDTH, HEIGHT);
}
void DisplayManager::update()
{
    m_Window.clear(sf::Color(100,100,100));
    sf::Event event;
    m_Window.pushGLStates();
    ImGui::SFML::Render(m_Window);
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
        }
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_Window.close();
            }
        }
        else if (event.type == sf::Event::Resized)
        {
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if (m_bClick)
            {
                m_Rotation.x += (m_Last.x - event.mouseMove.x) / 5.0;
                m_Rotation.y += (m_Last.y - event.mouseMove.y) / 5.0;
                m_Last.x = event.mouseMove.x;
                m_Last.y = event.mouseMove.y;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Button::Middle)
            {
                m_bClick = true;
                m_Last.x = event.mouseButton.x;
                m_Last.y = event.mouseButton.y;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Button::Middle)
            {
                m_bClick = false;
            }
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            m_uiZoom += event.mouseWheel.delta * 10;
            if (m_uiZoom < 20)
            {
                m_uiZoom = 20;
            }
        }
    }
    ImGui::SFML::Update(m_Window, m_Clock.restart());
    m_Window.popGLStates();
    m_Window.display();
}
bool DisplayManager::isOpen()
{
    return m_Window.isOpen();
}

float DisplayManager::GetAspectRatio() const
{
    sf::Vector2u size = m_Window.getSize();
    return (float)size.x / (float)size.y;
}

sf::Vector2f DisplayManager::GetRotation()
{
    return m_Rotation;
}

unsigned int DisplayManager::GetZoom()
{
    return m_uiZoom;
}