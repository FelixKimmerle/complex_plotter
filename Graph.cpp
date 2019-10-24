#include "Graph.hpp"

#include <iostream>

Graph::Graph(unsigned int pwidth, unsigned int pheight, std::string func) : m_func(func),
                                                                            mr((float)pwidth / (float)pheight),
                                                                            light(glm::vec3(0, 1000, 0), glm::vec3(1, 1, 1)),
                                                                            dir(glm::normalize(glm::abs(glm::vec3(100, 0, 100) - camera.position))),
                                                                            tr(0, 0, loader, func),
                                                                            rt(pwidth, pheight),
                                                                            m_Width(pwidth),
                                                                            m_Height(pheight)
{
    lx = Line(loader.loadLineToVAO(glm::vec3(0, 0, 0), glm::vec3(300, 0, 0), glm::vec3(1, 0, 0)), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
    ly = Line(loader.loadLineToVAO(glm::vec3(0, 0, 0), glm::vec3(0, 300, 0), glm::vec3(0, 1, 0)), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
    lz = Line(loader.loadLineToVAO(glm::vec3(0, 0, 0), glm::vec3(0, 0, 300), glm::vec3(0, 0, 1)), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 1);
    camera.position = glm::vec3(100, 0, 500);
    dir = glm::normalize(glm::abs(glm::vec3(100, 0, 100) - camera.position));
    isOpen = true;
    int i = 0;
    for (auto x = m_func.begin(); x != m_func.end(); x++)
    {
        m_Function[i] = *x;
        i++;
    }
    m_Function[i] = '\n';
}

Graph::~Graph()
{
}

void Graph::Update(sf::Vector2f rot, float zoom, ImVec2 size)
{
    camera.rotation.x = rot.y;
    camera.rotation.y = rot.x;
    camera.position = glm::vec3(0, 0, 0) + glm::vec3(dir.x * 500, dir.y * 500, dir.z * 500);
    tr.m_fScale = zoom / 200.f;
    rt.Resize(size.x, size.y);
    mr.ChangeAspectRatio((float)size.x / (float)size.y);
    rt.Use();
    mr.ProcessLine(lx);
    mr.ProcessLine(ly);
    mr.ProcessLine(lz);
    mr.ProcessTerrain(tr);
    mr.Render(light, camera);
    rt.UnUse();
    //std::cout << "Hallo welt" << std::endl;
}

unsigned int Graph::GetTextureID()
{
    return rt.GetTexture();
}

std::string Graph::GetName()
{
    return "ID: " + std::to_string((long long unsigned int)this);
}

bool *Graph::GetOpen()
{
    return &isOpen;
}

void Graph::DrawGui()
{
    ImGui::InputText("Update formula", m_Function, 128);
    ImGui::SameLine();
    if (ImGui::Button("Ok"))
    {
        m_func = std::string(m_Function);
        tr.Reload(0, 0, loader, m_func);
    }
}