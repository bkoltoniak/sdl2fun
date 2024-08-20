#include "logger.h"
#include "shader_utils.h"
#include "render.h"
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>

void close(SDL_GLContext &context, SDL_Window *window)
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Window *window = SDL_CreateWindow("OpenGL App", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    GLenum glewStatus = glewInit();
    if (GLEW_OK != glewStatus)
    {
        const GLubyte *error = glewGetErrorString(glewStatus);
        std::string errorStr(reinterpret_cast<const char *>(error));
        sdl2fun::logMessage(errorStr);
        close(context, window);
    }

    SDL_Event event;
    while (true)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                break;
            if (event.type == SDL_WINDOWEVENT)
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    glViewport(0, 0, (GLsizei)event.window.data1, (GLsizei)event.window.data2);
        }

        GLuint program = sdl2fun::initializeProgram();
        GLuint vertices = sdl2fun::loadVertices();
        sdl2fun::render(program, vertices);

        SDL_GL_SwapWindow(window);
    }

    close(context, window);
    return 0;
}