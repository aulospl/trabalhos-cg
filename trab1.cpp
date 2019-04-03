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
		// TODO
		
		// Renderiza catavento
		// TODO

		// Verifica e chama eventos e troca os buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
		y++;
	}
	else if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
		y--;
	}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		x--;
	}
	else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		x++;
	}
	else if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		a++;
	}
	else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		a--;
	}
	else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		*rotate = !rotate;
	}
}
