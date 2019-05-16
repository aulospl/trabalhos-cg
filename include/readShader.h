#ifndef READ_SHADER
#define READ_SHADER

#include <cstdio>
#include <cstring>
#include <string>
#include <glad/glad.h>


class ShaderProgram{
public:
    ShaderProgram(char * vertexShaderName, char * fragShaderName); // Le os arquivos de shader e cria o programa
    void use();
    int getProgram();
private:
    int shaderProgram;
};

char * readShader(char * filename);

#endif
