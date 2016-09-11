#ifndef TILEENGINEGL_SPRITE_H
#define TILEENGINEGL_SPRITE_H

#include <glm/glm.hpp>

#include "Mesh/Quad.h"

class Sprite
{
  private:
    glm::vec2 Position;
    glm::mat4 Model;
    int Depth;
    Quad m_Quad;

  public:
    Sprite(glm::vec2 position, int depth);

    glm::vec2 const &GetPosition()
    {
        return Position;
    }
    int const &GetDepth()
    {
        return Depth;
    }
    glm::mat4 const &GetModel()
    {
        return Model;
    }
    void SetPosition(glm::vec2 position)
    {
        Position = position;
        CalculateModel();
    }
    void SetDepth(int depth)
    {
        Depth = depth;
        CalculateModel();
    }

    void CalculateModel();
    void Render();
};

#endif