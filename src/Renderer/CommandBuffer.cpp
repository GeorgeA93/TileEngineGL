#include "CommandBuffer.h"

#include <algorithm>

#include "../Mesh/Mesh.h"

CommandBuffer::CommandBuffer() 
{

}

CommandBuffer::CommandBuffer()
{
    Clear();
}

void CommandBuffer::Push(Mesh *mesh, glm::mat4 transform)
{
    RenderCommand command = {};
    command.Mesh = mesh;
    command.Transform = transform;
    RenderCommands.push_back(command);
}

void CommandBuffer::Clear()
{
    RenderCommands.clear();
}

bool customRenderSort(RenderCommand a, RenderCommand b)
{
    return true;
}

void CommandBuffer::Sort()
{
    std::sort(RenderCommands.begin(), RenderCommands.end(), customRenderSort);
}

std::vector<RenderCommand> CommandBuffer::GetRenderCommands()
{
    return RenderCommands
}