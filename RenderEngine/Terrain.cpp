#include <vector>
#include "Terrain.hpp"
#include <cmath>

Terrain::Terrain(int gridX, int gridZ, Loader &loader, std::string func)
	: m_x(gridX * SIZE), m_z(gridZ * SIZE), rotation(0)
{
	MathParser mp;
	mp.Parse(func);
	pr = mp.Calc();
	pr.CalcStack();
	pr.Print();
	for (int i = 0; i < VERTEX_COUNT + 1; i++)
	{
		for (int j = 0; j < VERTEX_COUNT + 1; j++)
		{
			data[i][j] = (pr.Calc(std::complex<float>((i - 51.f) / 10.f, (j - 51.f) / 10.f)).real());
		}
	}
	pr.Print();
	m_model = GenerateTerrain(loader);
	m_fScale = 1.f;
}

void Terrain::Reload(int gridX, int gridZ, Loader &loader, std::string func)
{
	m_x = gridX * SIZE;
	m_z = gridZ * SIZE;
	rotation = glm::vec3(0);

	MathParser mp;
	mp.Parse(func);
	pr = mp.Calc();
	pr.CalcStack();
	pr.Print();
	for (int i = 0; i < VERTEX_COUNT + 1; i++)
	{
		for (int j = 0; j < VERTEX_COUNT + 1; j++)
		{
			data[i][j] = (pr.Calc(std::complex<float>((i - 51.f) / 10.f, (j - 51.f) / 10.f)).real());
		}
	}
	pr.Print();
	m_model = GenerateTerrain(loader);
	m_fScale = 1.f;
}

Terrain::~Terrain()
{
}

float Terrain::getHeight(unsigned int x, unsigned int y)
{
	x++;
	y++;

	if (x < 0)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (x > VERTEX_COUNT - 1)
	{
		x = 101;
	}
	if (y > VERTEX_COUNT - 1)
	{
		y = 101;
	}
	return data[x][y];
}

glm::vec3 Terrain::calculateNormal(int x, int z)
{
	float heightL = getHeight(x - 1, z);
	float heightR = getHeight(x + 1, z);
	float heightD = getHeight(x, z - 1);
	float heightU = getHeight(x, z + 1);

	glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}

RawModel Terrain::GenerateTerrain(Loader &loader)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<glm::vec3> vertices(count), normals(count);
	std::vector<unsigned int> indices(6 * (VERTEX_COUNT - 1) * VERTEX_COUNT);
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			vertices[vertexPointer] = glm::vec3(
				(float)j / ((float)VERTEX_COUNT - 1) * SIZE,
				getHeight(i, j),
				(float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			normals[vertexPointer] = calculateNormal(i, j);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz * VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(vertices, normals, indices);
}