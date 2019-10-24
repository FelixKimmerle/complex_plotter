#include "Loader.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Loader::Loader(/* args */)
{
}

Loader::~Loader()
{
    glDeleteVertexArrays(vaos.size(), &vaos[0]);
    glDeleteBuffers(vbos.size(), &vbos[0]);
    glDeleteTextures(textures.size(), &textures[0]);
}

unsigned int Loader::createVAO()
{
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}
void Loader::storeDataInAttributeList(unsigned int num, unsigned int coordinateSize, const void *data, unsigned int size)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(num, coordinateSize, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Loader::unbindVAO()
{
    glBindVertexArray(0);
}
/*
std::vector<glm::vec3> CalculateNormals(const std::vector<glm::vec3> &positions, const std::vector<unsigned int> &indices)
{
    std::vector<glm::vec3> Result(positions.size());
    std::map<unsigned int, std::vector<glm::vec3>> all;
    for (auto x = indices.begin(); x != indices.end(); x++)
    {
        unsigned int index1 = *(x++);
        unsigned int index2 = *(x++);
        unsigned int index3 = *(x);
        glm::vec3 a = positions[index1];
        glm::vec3 b = positions[index2];
        glm::vec3 c = positions[index3];
        glm::vec3 ab = a - b;
        glm::vec3 ac = a - c;
        glm::vec3 norm = glm::normalize(glm::cross(ab, ac));
        all[index1].push_back(norm);
        all[index2].push_back(norm);
        all[index3].push_back(norm);
    }
    for (auto x = all.begin(); x != all.end(); x++)
    {
        glm::vec3 n;
        for (auto xx = x->second.begin(); xx != x->second.end(); xx++)
        {
            n += *xx;
        }
        n /= glm::vec3(x->second.size(), x->second.size(), x->second.size());
        std::cout << x->second.size() << " " << n.x / x->second.size() << " " << n.y / x->second.size() << " " << n.z / x->second.size() << std::endl;
        Result[x->first] = n;
    }

    return Result;
}
*/

RawModel Loader::loadToVAO(const std::vector<glm::vec3> &positions, const std::vector<glm::vec3> &normals, const std::vector<unsigned int> &indices)
{
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, &positions[0], positions.size() * sizeof(glm::vec3));
    storeDataInAttributeList(1, 3, &normals[0], normals.size() * sizeof(glm::vec3));
    unbindVAO();
    return RawModel(vaoID, indices.size());
}

void Loader::bindIndicesBuffer(const std::vector<unsigned int> &indices)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
}
RawModel Loader::loadLineToVAO(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color)
{
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(std::vector<unsigned int>{0, 1});
    std::vector<glm::vec3> positions{pos1, pos2};
    storeDataInAttributeList(0, 3, &positions[0], positions.size() * sizeof(glm::vec3));
    std::vector<glm::vec3> colors{color, color};
    storeDataInAttributeList(1, 3, &colors[0], colors.size() * sizeof(glm::vec3));
    unbindVAO();
    return RawModel(vaoID, 2);
}