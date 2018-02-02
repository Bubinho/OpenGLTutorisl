#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>
#include <stdlib.h>  

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void move(float *balls, float *vel);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int NUM_METABALLS = 10;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

														// set up vertex data (and buffer(s)) and configure vertex attributes
											// ------------------------------------------------------------------
	float vertices[] = {
		// positions         
		-1.0f, 1.0f,  // topleft
		-1.0f, -1.0f,  // bottom left
		1.0f, 1.0f, // top right
		1.0f, -1.0f // bottopm right 

	};
	//glad_glViewport(0, 0, 400, 400);
	
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	
	



	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);


	// simulaztion setuü
	float *metaballs = new float[NUM_METABALLS * 3]; // for uniform
	float *velocities = new float[NUM_METABALLS * 2];
	for (int i = 0; i < NUM_METABALLS; i++) {
		float radius = 40;//(rand() % 9 * 0.1 + 10) * 40;
		
		metaballs[3 * i + 0] = ((rand() % 9) * 0.1) * (SCR_WIDTH - 2 * radius) + radius;
		metaballs[3 * i + 1] = ((rand() % 9) * 0.1) * (SCR_HEIGHT - 2 * radius) + radius;
		metaballs[3 * i + 2] = radius;
		//std::cout << metaballs[3 * i + 0] << std::endl;

		velocities[2 * i + 0] = ((rand() % 10 + 1)) - 5;
		velocities[2 * i + 1] = ((rand() % 10 + 1)) - 5;
	}
	/*GLfloat *metaballs = new float[3];
	metaballs[ 0] = 400.0f;
	metaballs[ 1] = 400.0f;
	metaballs[2] = 10.0f;*/

	
	// texture
	/*unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_1D, texture);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, NUM_METABALLS, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, metaballs);
	
	
	
	
	
	
	//glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 5, 0, GL_RGB, GL_UNSIGNED_BYTE, metaballs);
	



	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		//move balls
		move(metaballs, velocities);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		ourShader.use();
		//glBindTexture(GL_TEXTURE_1D, texture);
		ourShader.setFloat3Vector("metas", metaballs, 10);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void move(float *balls, float *vel) 
{
	for (int i = 0; i < NUM_METABALLS; i++) 
	{
		float x  = balls[3 * i + 0];
		float y = balls[3 * i + 1];
		float r = balls[3 * i + 2];
		float velX = vel[2 * i + 0];
		float velY = vel[2 * i + 1];

		x += velX;
		y += velY;

		if (x <= 0 ||x >= SCR_WIDTH) {
			velX *= -1.f;
			vel[2 * i + 0] = velX;
		}
		if (y <= 0 || y >= SCR_HEIGHT) {
			velY *= -1.f;
			vel[2 * i + 1] = velY;
		}

		balls[3 * i + 0] = x;
		balls[3 * i + 1] = y;
		
	}
	
}