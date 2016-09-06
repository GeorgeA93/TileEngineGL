#ifndef TILEENGINEGL_MESH_H
#define TILEENGINEGL_MESH_H

#include <vector>
#include <glm/glm.hpp>

enum TOPOLOGY
{
  TRIANGLE_STRIP
};

class Mesh
{
public:
  unsigned int VAO = 0;
  unsigned int VBO;
  unsigned int EBO;
  std::vector<glm::vec3> Positions;
  std::vector<glm::vec2> UV;
  std::vector<glm::vec3> Normals;
  std::vector<glm::vec3> Tangents;
  std::vector<glm::vec3> Bitangents;

  TOPOLOGY Topology;
  std::vector<unsigned int> Indices;

  Mesh();
  Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
  Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);

  void Finalize(bool interleaved = true);
};

#endif