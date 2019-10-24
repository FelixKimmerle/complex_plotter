#include "TerrainRenderer.hpp"
#include "Maths.hpp"

TerrainRenderer::TerrainRenderer(TerrainShader &shader, glm::mat4 &projectionMatrix)
	: m_shader(shader)
{
	// Load the projection matrix into the shader
	m_shader.Use();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.UnUse();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::Render(std::vector<Terrain> &terrains)
{
	for (Terrain &terrain : terrains)
	{
		BindTerrain(terrain);
		RenderTerrain(terrain);
		UnbindTerrain();
	}
}

void TerrainRenderer::BindTerrain(const Terrain &terrain)
{
	// Get the RawModel from the textured model
	glBindVertexArray(terrain.GetModel().vaoID);
	m_shader.LoadShineVariables(1, 0);
	// Enable the attrib arrays
	for (unsigned int i = 0; i < 2; i++)
		glEnableVertexAttribArray(i);
	// Load shine from the texture
}

void TerrainRenderer::UnbindTerrain()
{
	// Disable the attrib arrays
	for (unsigned int i = 0; i < 2; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

void TerrainRenderer::RenderTerrain(const Terrain &terrain)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformMatrix(createTransformationMatrix(glm::vec3(terrain.GetX() - 100, 0, terrain.GetZ() - 100), terrain.rotation, terrain.m_fScale));
	// Draw the model
	glDrawElements(GL_TRIANGLES, terrain.GetModel().vertexCount, GL_UNSIGNED_INT, 0);
}
