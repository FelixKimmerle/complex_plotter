

#include <glm/gtc/matrix_transform.hpp>
#include "MasterRenderer.hpp"
#include "Maths.hpp"
#include <Imgui/imgui-SFML.h>
#include <Imgui/imgui.h>

MasterRenderer::MasterRenderer(float aspectRatio)
	: m_projectionMatrix(/*glm::ortho(-200.f,200.f,-200.f,200.f,m_NEAR_PLANE,m_FAR_PLANE)*/ glm::perspective(m_FOV, aspectRatio, m_NEAR_PLANE, m_FAR_PLANE)),
	  m_terrainRenderer(TerrainRenderer(m_terrainShader, m_projectionMatrix)),
	  m_lineRenderer(LineRenderer(m_lineShader, m_projectionMatrix))
{
	// Don't draw faces we can't see
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	// Tell OpenGL to test for depth
	glEnable(GL_DEPTH_TEST);
	// Set clear color and clear the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	// Enable alpha blend
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable Antialiasing
	glEnable(GL_MULTISAMPLE);
	glLineWidth(2);
}

void MasterRenderer::ChangeAspectRatio(float p_fRatio)
{
	m_projectionMatrix = glm::perspective(m_FOV, p_fRatio, m_NEAR_PLANE, m_FAR_PLANE);
	m_lineShader.Use();
	m_lineShader.LoadProjectionMatrix(m_projectionMatrix);
	m_lineShader.UnUse();

	m_terrainShader.Use();
	m_terrainShader.LoadProjectionMatrix(m_projectionMatrix);
	m_terrainShader.UnUse();
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Render(const Light &light, const Camera &camera)
{
	//rt.bind();

	// Clear buffers and activate the shader
	// Load terrain shader parameters and render terrains
	m_terrainShader.Use();
	m_terrainShader.LoadLight(light, 0.4f);
	m_terrainShader.LoadViewMatrix(crateViewMatrix(camera));
	m_terrainRenderer.Render(terrains);
	m_terrainShader.UnUse();
	terrains.clear();

	m_lineShader.Use();
	m_lineShader.LoadViewMatrix(camera);
	m_lineRenderer.Render(lines);
	m_lineShader.UnUse();

	lines.clear();

	//rt.unbind();
}

void MasterRenderer::ProcessTerrain(const Terrain &terrain)
{
	// Add terrain to list
	terrains.push_back(terrain);
}
void MasterRenderer::ProcessLine(const Line &line)
{
	lines.push_back(line);
}