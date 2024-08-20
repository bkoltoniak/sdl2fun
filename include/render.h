#include <GL/glew.h>

namespace sdl2fun
{
    GLuint initializeProgram();
    GLuint loadVertices();
    void render(GLuint program, GLint vertices);
}