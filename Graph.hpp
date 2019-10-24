#pragma once

#include "RenderEngine/MasterRenderer.hpp"
#include "RenderEngine/Loader.hpp"
#include "RenderEngine/Light.hpp"
#include "RenderEngine/RenderTarget.hpp"

#include <Imgui/imgui.h>

class Graph
{
  private:
    MasterRenderer mr;
    Line lx, ly, lz;
    Loader loader;
    Camera camera;
    Light light;
    glm::vec3 dir;
    Terrain tr;
    RenderTarget rt;
    unsigned int m_Width;
    unsigned int m_Height;
    std::string m_func;
    bool isOpen;

    char m_Function[128];

  public:
    Graph(unsigned int pwidth, unsigned int pheight,std::string func);
    ~Graph();
    void Update(sf::Vector2f rot, float zoom, ImVec2 size);
    unsigned int GetTextureID();
    std::string GetName();
    bool * GetOpen();
    void DrawGui();
};
