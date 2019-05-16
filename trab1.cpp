#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "readShader.h"
#include "matrixArith.h"
#include <cmath>



using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window, int *x, int *y, int *a, bool *rotate);


int main( int argc, char **argv ){
	const int x_min = -50;
	const int x_max = 50;
	const int y_min = -50;
	const int y_max = 50;
	int x, y, rotation_speed;
	bool rotate = true;
	float cur_angle = 0;
	GLfloat lastFrame, deltaTime; // Estabilizar a imagem em funcao do fps
	// Posição e velocidade iniciais
	x = 0;
	y = 0;
	rotation_speed = 40;

	// Inicializando glfw e configurando contexto
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	width_now = 1024;
	height_now = 768;
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
	ShaderProgram prog("vtx_shader.glsl", "frag_shader.glsl");

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

	lastFrame = glfwGetTime();

	float *rotation_matrix = createIdentity4();
	float *translation_matrix = createIdentity4();

	while(!glfwWindowShouldClose(window)){
		// Processa entrada
		processInput(window, &x, &y, &rotation_speed, &rotate);

		// Renderização
		// TODO
		//
		// Background branco
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Ativa shader
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		prog.use();

		if (rotate){
			cur_angle += rotation_speed/40.0 * deltaTime;
		}

		rotation_matrix[0] = cos(cur_angle);
		rotation_matrix[1] = -sin(cur_angle);
		rotation_matrix[4] = sin(cur_angle);
		rotation_matrix[5] = cos(cur_angle);

		if (x < x_min){
			x = x_min;
		}

		if (x > x_max){
			x = x_max;
		}


		if (y < y_min){
			y = y_min;
		}

		if (y > y_max){
			y = y_max;
		}


		translation_matrix[3] = x/100.0;
		translation_matrix[7] = y/100.0;

		float* model_matrix = multMatrix4(translation_matrix, rotation_matrix);
		glUniformMatrix4fv(glGetUniformLocation(prog.getProgram(), "model"), 1, GL_TRUE, model_matrix);
		free (model_matrix);

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
	width_now = width;
	height_now = height;
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
	else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
