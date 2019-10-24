#pragma once

#include <vector>
#include "Shaders/LineShader.hpp"
#include "Line.hpp"

class LineRenderer
{
public:
	LineRenderer(LineShader& shader, glm::mat4& projectionMatrix);
	virtual ~LineRenderer();

	void Render(std::vector<Line>& terrains);
private:
	LineShader& m_shader;
	void BindLine(const Line& terrain);
	void UnbindLine();
	void RenderLine(const Line& terrain);
};