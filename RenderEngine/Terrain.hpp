#pragma once

#include "RawModel.hpp"
#include "Loader.hpp"
#include "Math/MathParser.hpp"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader &loader, std::string func);
	virtual ~Terrain();

	inline float GetX() const { return m_x; }
	inline float GetZ() const { return m_z; }
	inline RawModel GetModel() const { return m_model; }
	glm::vec3 rotation;
	float m_fScale;
	void Reload(int gridX, int gridZ, Loader &loader, std::string func);

private:
	const float SIZE = 200;
	const int VERTEX_COUNT = 101;
	float m_x, m_z;
	RawModel m_model;
	RawModel GenerateTerrain(Loader &loader);
	Programm pr;
	float data[102][102];
	float getHeight(unsigned int x, unsigned int y);
	glm::vec3 calculateNormal(int x, int z);
};