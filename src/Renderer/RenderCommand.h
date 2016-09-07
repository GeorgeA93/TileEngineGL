#ifndef TILEENGINEGL_RENDER_COMMAND_H
#define TILEENGINEGL_RENDER_COMMAND_H

#include <glm/glm.hpp>

class Mesh;

struct RenderCommand 
{
    glm::mat4 Transform;
    Mesh *Mesh;
};

#endif