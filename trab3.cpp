#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <readShader.h>
#include <matrixArith.h>
#include <cmath>
#include <Model.h>
#include <Camera.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window, int *rot_dir, float *scale, char* eixo, Camera &cam);

float* changeRotationsAxis(char axis, float *rotation_matrix);


float cur_angle = 0;
bool useTexture = true;

int main( int argc, char **argv ){
	// const int x_min = -50;
	// const int x_max = 50;
	// const int y_min = -50;
	// const int y_max = 50;
	char eixo = 'y';
	int rot_dir = 1;
	float scale = 1.0, rotation_speed = 0.1;
	bool rotate = true;
	float max_scale = 100;
	// float cur_angle = 0;
	GLfloat lastFrame, deltaTime; // Estabilizar a imagem em funcao do fps
	// Posição e velocidade iniciais
	rotation_speed = 40;

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
	glEnable(GL_DEPTH_TEST);

	// Configura função de callback para redimencionar viewport
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// build and compile shader programs
	// ---------------------------------
	ShaderProgram prog("shaders/vtx_shader.glsl", "shaders/frag_shader.glsl");

	// set up camera
	float pos[3] = {0.0, 0.0, 0.0};
	float dir[3] = {0.0, 0.0, 1.0};
	float up[3] = {0.0, 1.0, 0.0};

	Camera ourCamera(pos, dir, up);


	Model *ourModel;
	if (argc > 1){
		ourModel = new Model(argv[1]);
	}else{
		ourModel = new Model("models/IronMan/IronMan.obj");
	}


	lastFrame = glfwGetTime();

	float *rotation_matrix = createIdentity4();
	float *translation_matrix = createIdentity4();
	float *scale_matrix = createIdentity4();

	max_scale = 1.0/(ourModel->maxCoordinate);
	scale = 0.75 * max_scale;

	while(!glfwWindowShouldClose(window)){
		rot_dir = 1;
		// Processa entrada
		processInput(window, &rot_dir, &scale, &eixo, ourCamera);

		if (scale > max_scale){
			scale = max_scale;
		}

		// Renderização
		// Background branco
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Ativa shader
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		prog.use();

		if (rotate){
			cur_angle += rotation_speed/50.0 * deltaTime * rot_dir;
		}
		rotation_matrix = changeRotationsAxis(eixo, rotation_matrix);

		translation_matrix[3] = 0.0;
		translation_matrix[7] = 0.0;

		scale_matrix[0] = scale;
		scale_matrix[5] = scale;
		scale_matrix[10] = scale;


		float* model_matrix = multMatrix4(translation_matrix, rotation_matrix);
		model_matrix = multMatrix4(model_matrix, scale_matrix);

		glUniformMatrix4fv(glGetUniformLocation(prog.getProgram(), "model"), 1, GL_TRUE, model_matrix);
		free (model_matrix);

		// Renderiza catavento

		ourModel->draw(prog, useTexture);

		// Verifica e chama eventos e troca os buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
   // de-alocate resources
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
void processInput(GLFWwindow *window, int *rot_dir, float *scale, char *eixo, Camera &cam){
	float xAxis = 0.0, zAxis = 0.0;
	if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
		*eixo = 'x';
	}
	else if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
		*eixo = 'y';
	}
	else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
		*eixo = 'z';
	}
	else if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
		*scale = *scale * 1.1;
	}
	else if(glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
		*scale = *scale / 1.1;
	}
	else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS){
		*rot_dir = -1;
	}
	else if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
		useTexture = !useTexture;
	}
	else if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		zAxis += 1.0;
	}
	else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		xAxis -= 1.0;
	}
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		zAxis -= 1.0;
	}
	else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		xAxis += 1.0;
	}
	cam.moveCamera(xAxis, 0.0, zAxis);

}


float* changeRotationsAxis(char axis, float *rotation_matrix){
	switch(axis){
	case 'x':
		free(rotation_matrix);
		rotation_matrix = createIdentity4();
		rotation_matrix[5] = cos(cur_angle);
		rotation_matrix[6] = -sin(cur_angle);
		rotation_matrix[9] = sin(cur_angle);
		rotation_matrix[10] = cos(cur_angle);
		break;
	case 'y':
		free(rotation_matrix);
		rotation_matrix = createIdentity4();
		rotation_matrix[0] = cos(cur_angle);
		rotation_matrix[2] = -sin(cur_angle);
		rotation_matrix[8] = sin(cur_angle);
		rotation_matrix[10] = cos(cur_angle);
		break;
	case 'z':
		free(rotation_matrix);
		rotation_matrix = createIdentity4();
		rotation_matrix[0] = cos(cur_angle);
		rotation_matrix[1] = -sin(cur_angle);
		rotation_matrix[4] = sin(cur_angle);
		rotation_matrix[5] = cos(cur_angle);
		break;
	}
	return rotation_matrix;
}
