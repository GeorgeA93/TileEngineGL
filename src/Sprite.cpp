#include "Sprite.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(glm::vec2 position, int depth)
{
    Position = position;
    Depth = depth;
    CalculateModel();
}

void Sprite::CalculateModel()
{
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(Position, -Depth));
    // Scale
    // Rotate
    Model = model;
    Quad q(0.32, 0.32);
    m_Quad = q;
}

void Sprite::Render()
{     
    glBindVertexArray(m_Quad.VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Quad.Positions.size());
    glBindVertexArray(0);
}