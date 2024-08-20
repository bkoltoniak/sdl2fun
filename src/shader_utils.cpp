#include "shader_utils.h"
#include "logger.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace sdl2fun
{
    GLuint CreateShader(GLenum shaderType, const std::string &shaderPath)
    {
        GLuint shader = glCreateShader(shaderType);
        std::ifstream shaderFile(shaderPath);

        if (shaderFile.is_open())
        {
            const std::string shaderContent((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

            const char *strFileData = shaderContent.c_str();
            glShaderSource(shader, 1, &strFileData, NULL);
            glCompileShader(shader);

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint logLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

                GLchar *infoLog = new GLchar[logLength + 1];
                glGetShaderInfoLog(shader, logLength, NULL, infoLog);

                logMessage("Error:" + getShaderTypeString(shaderType) + " shader compilation failure: " + std::string(infoLog) + "\n");
                delete[] infoLog;
            }
        }
        else
        {
            logMessage("Error: reading shader " + shaderPath + "\n");
        }

        return shader;
    }

    GLuint CreateProgram(std::vector<GLuint> &shaders)
    {
        GLuint program = glCreateProgram();

        for (GLint shader : shaders)
            glAttachShader(program, shader);

        glLinkProgram(program);
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint logLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            GLchar *infoLog = new GLchar[logLength + 1];
            glGetProgramInfoLog(program, logLength, NULL, infoLog);
            logMessage("Error: error linking shaders: " + std::string(infoLog) + "\n");
            delete[] infoLog;
        }

        for (GLuint shader : shaders)
            glDetachShader(program, shader);

        return program;
    }

    std::string getShaderTypeString(GLenum shaderType)
    {
        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            return "vertex";
        case GL_GEOMETRY_SHADER:
            return "geometry";
        case GL_FRAGMENT_SHADER:
            return "fragment";
        default:
            return "";
        }
    }
}