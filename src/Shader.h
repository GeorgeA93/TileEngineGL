//
// Created by George Allen on 15/08/2016.
//

#ifndef TILEENGINEGL_SHADER_H
#define TILEENGINEGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

class Shader
{
  public:
    GLuint Program;

    Shader(const GLchar *vPath, const GLchar *fPath);

    // Use the program
    void Use();
};

#endif //TILEENGINEGL_SHADER_H
