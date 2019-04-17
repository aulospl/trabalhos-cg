#include "readShader.h"

ShaderProgram::ShaderProgram(char * vertexShaderName, char * fragShaderName){
	// vertex shader
	char * vshader = readShader(vertexShaderName);
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vshader, NULL);
	glCompileShader(vertexShader);
	// Check for shader compile errors
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED%s\n", infolog);
		// return -3;
	}

	// fragment shader
	char * fshader = readShader(fragShaderName);
	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fshader, NULL);
	glCompileShader(fragShader);
	// Check shader compile error
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED%s\n", infolog);
		// return -4;
	}

	// link shaders
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragShader);
	glLinkProgram(this->shaderProgram);

	// check linking errors
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infolog);
		fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED%s\n", infolog);
		// return -5;
	}

}

void ShaderProgram::use(){
	glUseProgram(this->shaderProgram);
}


char * readShader(char * filename){
	if (filename == NULL){
		return NULL;
	}
	else{
		std::FILE *file = std::fopen(filename, "r");
		std::string contents;
		if(file){
			std::fseek(file, 0, SEEK_END);
			size_t len = std::ftell(file);
			std::fseek(file, 0, SEEK_SET);
			contents.resize(len+1);
			std::fread(&contents[0], 1, len, file);
			fclose(file);
			char *shader = new char[contents.length()+1];
			std::strcpy(shader, contents.c_str());
			return shader;
		}
		else{
			return NULL;
		}
	}
}
