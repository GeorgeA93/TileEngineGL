#ifndef TILEENGINEGL_COMMAND_BUFFER_H
#define TILEENGINEGL_COMMAND_BUFFER_H

#include <vector>
#include <glm/glm.hpp>
#include "RenderCommand.h"

class Mesh;

class CommandBuffer
{
  public:
    CommandBuffer();
    ~CommandBuffer();

    void Push(Mesh *mesh, glm::mat4 transform);
    void Clear();
    void Sort();

    std::vector<RenderCommand> GetRenderCommands();

  private:
    std::vector<RenderCommand> RenderCommands;
};

#endif