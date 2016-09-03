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

    Shader(const GLchar* vPath, const GLchar* fPath)
    {
        std::string shaderPath = PROJECT_SOURCE_DIR "/res/shaders/";
        std::string vertexPath = shaderPath + vPath;
        std::string fragmentPath = shaderPath + fPath;

        std::cout << vertexPath << std::endl;
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ensures ifstream objects can throw exceptions
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);

        try
        {
            //open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read the files buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close the file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert the stream to a string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        // Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // Print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER:VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER:FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //Shader Program
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);

        // Print linking errors
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER:LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Delete shaders as they are linked to the program!
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // Use the program
    void Use()
    {
        glUseProgram(this->Program);
    }
};

#endif //TILEENGINEGL_SHADER_H
