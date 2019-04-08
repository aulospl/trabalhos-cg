#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "readShader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window, int *x, int *y, int *a, bool *rotate);

int main( int argc, char **argv ){
	int x, y, a;
	bool rotate = true;
	
	// Posição e velocidade iniciais
	x = 512;
	y = 384;
	a = 1;

	// Inicializando glfw e configurando contexto
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(1024, 768, "Trabalho 1", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create GLFW Window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	

	// Inicializando glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Cria viewport
	glViewport(0, 0, 1024, 768);
	
	// Configura função de callback para redimencionar viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	/*
	 * TODO:
	 *			Definir vertices dos triangulos
	 *			Carregar VBOs VBAs
	 *			Carregar shaders
	 */
	float firstTriangle[] = {
		0.0f, 0.0f, 0.0f,		//left
		0.5f, 0.0f, 0.0f,		//right
		0.25f, -0.2f, 0.0f		//top
	};
	float secondTriagle[] = {
		0.0f, 0.0f, 0.0f,		//top
		-0.2f, -0.25f, 0.0f,	//left
		0.0f, -0.5f, 0.0f		//bottom
	};
	float thirdTriangle[] = {
		0.0f, 0.0f, 0.0f,		//right
		-0.25f, 0.2f, 0.0f,		//top
		-0.5f, 0.0f, 0.0f		//left
	};
	float fourthTriagle[] = {
		0.0f, 0.0f, 0.0f,		//bottom
		0.2f, 0.25f, 0.0f,		//right
		0.0f, 0.5f, 0.0f		//top
	};

	// build and compile shader programs
	// ---------------------------------
	// vertex shader
	char * vshader = readShader("vtx_shader.glsl");
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vshader, NULL);
	glCompileShader(vertexShader);
	// Check for shader compile errors
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << endl;
		return -3;
	}
	// fragment shader
	char * fshader = readShader("frag_shader.glsl");
	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fshader, NULL);
	glCompileShader(fragShader);
	// Check shader compile error
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << endl;
		return -4;
	}
	
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	// check linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << endl;
		return -5;
	}	
	
	// Set VBO and VAOs and bind to triangles
	unsigned int VBOs[4], VAOs[4];
	glGenVertexArrays(4, VAOs);
	glGenBuffers(4, VBOs);
	
	// first triangle setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second triagle setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriagle), secondTriagle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , (void*)0);
	glEnableVertexAttribArray(0);

	// third triangle setup
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// fourth triagle setup
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fourthTriagle), fourthTriagle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , (void*)0);
	glEnableVertexAttribArray(0);

	
	while(!glfwWindowShouldClose(window)){
		// Processa entrada
		processInput(window, &x, &y, &a, &rotate);

		// Renderização
		// TODO
		//
		// Background branco
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Ativa shader
		glUseProgram(shaderProgram);
		
		// Renderiza catavento
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Verifica e chama eventos e troca os buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
   // de-alocate resources
	glDeleteVertexArrays(4, VAOs);
	glDeleteBuffers(4, VBOs); 
	glfwTerminate();

	return 0;
}

/*
 * Função de callback para redimencionar o viewport quando a janela é redimencionada
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
 	glViewport(0, 0, width, height);
}

/*
 * Função que processa entrada do usuário
 * x = cordenada x do catavento
 * y = cordenada y do catavento
 * a = velocidade angular
 * rotate = se o catavento gira ou esta parado
 */
void processInput(GLFWwindow *window, int *x, int *y, int *a, bool *rotate){
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		*y = *y+1;
	}
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		*y = *y-1;
	}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		*x = *x-1;
	}
	else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		*x = *x+1;
	}
	else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		*a = *a+1;
	}
	else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		*a = *a-1;
	}
	else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		*rotate = !*rotate;
	}
}
