#include "render.h"
#include "shader_utils.h"
#include <GL/glew.h>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <filesystem>

namespace sdl2fun
{
    GLuint initializeProgram()
    {
        std::vector<GLuint> shaders;

        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
        std::string binaryPath = std::string(buffer, (count > 0) ? count : 0);
        std::string binaryDir = std::filesystem::path(binaryPath).parent_path();

        shaders.push_back(CreateShader(GL_VERTEX_SHADER, binaryDir + "/assets/tut1.vert"));
        shaders.push_back(CreateShader(GL_FRAGMENT_SHADER, binaryDir + "/assets/tut1.frag"));

        GLuint program = CreateProgram(shaders);

        for (GLuint shader : shaders)
            glDeleteShader(shader);

        return program;
    }

    GLuint loadVertices()
    {
        GLuint buffer;
        const float vertices[] = {
            0.75f, 0.75f, 0.0f, 1.0f,
            0.75f, -0.75f, 0.0f, 1.0f,
            -0.75f, 0.75f, 0.0f, 1.0f,
        };

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        GLuint vao;
        glGenVertexArrays(1, &vao);
	    glBindVertexArray(vao);

        return buffer;
    }

    void render(GLuint program, GLint vertices)
    {
        glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindBuffer(GL_ARRAY_BUFFER, vertices);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glUseProgram(0);

    }
}