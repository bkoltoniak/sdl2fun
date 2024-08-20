#include <GL/glew.h>
#include <string>
#include <vector>

namespace sdl2fun
{
    GLuint CreateShader(GLenum eShaderType, const std::string &shaderPath);
    GLuint CreateProgram(std::vector<GLuint> &shaders);
    std::string getShaderTypeString(GLenum eShaderType);
}