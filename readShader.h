#ifndef READ_SHADER
#define READ_SHADER

#include <cstdio>
#include <cstring>
#include <string>
#include "include/glad/glad.h"


class ShaderProgram{
public:
    ShaderProgram(char * vertexShaderName, char * fragShaderName);
    void use();

private:
    int shaderProgram;
};

char * readShader(char * filename);

#endif
