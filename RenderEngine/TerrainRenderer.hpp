#pragma once

#include <vector>
#include "Shaders/TerrainShader.hpp"
#include "Terrain.hpp"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4& projectionMatrix);
	virtual ~TerrainRenderer();

	void Render(std::vector<Terrain>& terrains);
private:
	TerrainShader& m_shader;
	void BindTerrain(const Terrain& terrain);
	void UnbindTerrain();
	void RenderTerrain(const Terrain& terrain);
};