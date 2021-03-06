#include <glad/glad.h>

#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices)
{
    Positions = positions;
    Indices = indices;
}

Mesh::Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices)
{
    Positions = positions;
    UV = uv;
    Indices = indices;
}

void Mesh::Finalize(bool interleaved)
{
    if (!VAO)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    std::vector<float> data;
    if (interleaved)
    {
        for (int i = 0; i < Positions.size(); i++)
        {
            data.push_back(Positions[i].x);
            data.push_back(Positions[i].y);
            data.push_back(Positions[i].z);
            if (UV.size() > 0)
            {
                data.push_back(UV[i].x);
                data.push_back(UV[i].y);
            }
        }
    }
    else
    {
        for (int i = 0; i < Positions.size(); ++i)
        {
            data.push_back(Positions[i].x);
            data.push_back(Positions[i].y);
            data.push_back(Positions[i].z);
        }
        for (int i = 0; i < UV.size(); ++i)
        {
            data.push_back(UV[i].x);
            data.push_back(UV[i].y);
        }
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    if (Indices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
    }
    if (interleaved)
    {
        size_t stride = 3 * sizeof(float);
        if (UV.size() > 0)
        {
            stride += 2 * sizeof(float);
        }

        size_t offset = 0;
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
        offset += 3 * sizeof(float);
        if (UV.size() > 0)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
        }
    }
    glBindVertexArray(0);
}