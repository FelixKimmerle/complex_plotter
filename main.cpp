#include <iostream>
#include "RenderEngine/DisplayManager.hpp"
#include "RenderEngine/Loader.hpp"
#include "RenderEngine/MasterRenderer.hpp"
#include <Imgui/imgui-SFML.h>
#include <Imgui/imgui.h>
#include "RenderEngine/RenderTarget.hpp"
#include "Graph.hpp"

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

char text[128] = "";

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    DisplayManager dpm;
    dpm.create();

    // During init, enable debug outputS
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    std::vector<Graph *> Graphs;

    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;

    sf::Clock clock;
    unsigned int uiFps = 0;

    ImVec2 uv0(0, 1);
    ImVec2 uv1(1, 0);

    Graph *focused = nullptr;

    while (dpm.isOpen())
    {
        for (unsigned int i = 0; i < Graphs.size(); i++)
        {
            if (*Graphs[i]->GetOpen())
            {
                if (ImGui::Begin(Graphs[i]->GetName().c_str(), Graphs[i]->GetOpen(), ImVec2(800, 600)))
                {
                    ImVec2 wsize = ImGui::GetWindowSize();
                    Graphs[i]->Update(dpm.GetRotation(), dpm.GetZoom(), wsize);
                    glViewport(0, 0, 1280, 720);

                    if (ImGui::IsWindowFocused())
                    {
                        //ImGui::Begin("Config");
                        //ImGui::End();
                        focused = Graphs[i];
                        std::cout << Graphs[i]->GetName() << std::endl;
                    }

                    ImGui::Image((void *)(intptr_t)Graphs[i]->GetTextureID(), ImVec2(wsize.x - 17, wsize.y - 35), uv0, uv1);
                }
                ImGui::End();
            }
            else
            {
                delete Graphs[i];
                Graphs.erase(Graphs.begin() + i);
                i--;
            }
        }

        if (ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::InputText("Input formula", text, 128);
            ImGui::SameLine();
            if (ImGui::Button("Ok"))
            {
                Graphs.push_back(new Graph(800, 600, std::string(text)));
                text[0] = '\0';
            }
        }
        ImGui::End();
        uiFps++;
        if (clock.getElapsedTime().asMilliseconds() > 1000)
        {
            std::cout << uiFps << std::endl;
            uiFps = 0;
            clock.restart();
        }
        dpm.update();

        if (focused != nullptr)
        {
            ImGui::Begin("Config",nullptr,ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Text(focused->GetName().c_str());
            focused->DrawGui();
            ImGui::End();
        }
    }

    for (auto xxx = Graphs.begin(); xxx != Graphs.end(); xxx++)
    {
        delete *xxx;
    }
    return 0;
}
