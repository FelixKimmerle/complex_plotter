#include "LineRenderer.hpp"
#include "Maths.hpp"

LineRenderer::LineRenderer(LineShader& shader, glm::mat4& projectionMatrix)
	: m_shader(shader)
{
	// Load the projection matrix into the shader
	m_shader.Use();
	m_shader.LoadProjectionMatrix(projectionMatrix);
	m_shader.UnUse();
}


LineRenderer::~LineRenderer()
{
}


void LineRenderer::Render(std::vector<Line>& terrains)
{
	for (Line& terrain : terrains)
	{
		BindLine(terrain);
		RenderLine(terrain);
		UnbindLine();
	}
}


void LineRenderer::BindLine(const Line& terrain)
{
	// Get the RawModel from the textured model
	glBindVertexArray(terrain.model.vaoID);
	// Enable the attrib arrays
	for (unsigned int i = 0; i < 2; i++)
		glEnableVertexAttribArray(i);
	// Load shine from the texture
}


void LineRenderer::UnbindLine()
{
	// Disable the attrib arrays
	for (unsigned int i = 0; i < 2; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}


void LineRenderer::RenderLine(const Line& terrain)
{
	// Load the transformation matrix into the shader
	m_shader.LoadTransformationMatrix(createTransformationMatrix(terrain.position, terrain.rotation, 1));
	// Draw the model
	glDrawElements(GL_LINES, terrain.model.vertexCount, GL_UNSIGNED_INT, 0);
}

