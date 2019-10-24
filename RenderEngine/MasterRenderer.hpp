#pragma once

#include "TerrainRenderer.hpp"
#include "Camera.hpp"
#include "LineRenderer.hpp"
#include "RenderTexture.hpp"

class MasterRenderer
{
public:
	MasterRenderer(float aspectRatio);
	virtual ~MasterRenderer();

	void Render(const Light& light, const Camera &camera);
	void ProcessTerrain(const Terrain& terrain);
	void ProcessLine(const Line& line);
	void ChangeAspectRatio(float p_fRatio);
private:
	const float m_FOV = 70;
	const float m_NEAR_PLANE = 0.1f;
	const float m_FAR_PLANE = 1000;
	glm::mat4 m_projectionMatrix;
	TerrainShader m_terrainShader;
	TerrainRenderer m_terrainRenderer;

	LineShader m_lineShader;
	LineRenderer m_lineRenderer;


	std::vector<Terrain> terrains;
	std::vector<Line> lines;
};
