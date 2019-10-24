#pragma once
#include "RawModel.hpp"
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Loader
{
private:
  unsigned int createVAO();
  void storeDataInAttributeList(unsigned int num, unsigned int coordinateSize, const void *data, unsigned int size);
  void unbindVAO();
  void bindIndicesBuffer(const std::vector<unsigned int> &indices);

  std::vector<unsigned int> vaos;
  std::vector<unsigned int> vbos;
  std::vector<unsigned int> textures;

public:
  Loader(/* args */);
  ~Loader();
  RawModel loadToVAO(const std::vector<glm::vec3> &positions, const std::vector<glm::vec3> &normals, const std::vector<unsigned int> &indices);
  RawModel loadLineToVAO(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color);
};
