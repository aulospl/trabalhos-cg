#include "readShader.h"

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


