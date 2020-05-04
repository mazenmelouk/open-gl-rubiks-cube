#include <globalvariables.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <Angel.h>
#include <material.h>
#include <light_source.h>
#include <ctime>
#include <rubikscube.h>
#include <initfunctions.h>
#include <animations.h>
#include <inputfunctions.h>

using namespace std;

void renderAll()
{
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		//send data of shape[i] to shader

		glUniform4fv(light_position_loc, 1, lights[0]->position);
		glUniform4fv(eye_position_loc, 1, eye);
		glUniform4fv(ambient_product_loc, 1, lights[0]->ambient * shapes[i]->material.ambientK);
		glUniform4fv(diffuse_product_loc, 1, lights[0]->diffuse * shapes[i]->material.diffuseK);
		glUniform4fv(specular_product_loc, 1, lights[0]->specular * shapes[i]->material.specularK);
		glUniform1f(shininess_loc, shapes[i]->material.shininess);
		glUniform3fv(scale_loc, 1, shapes[i]->scale);
		glUniform3fv(translation_loc, 1, shapes[i]->translation);
		glUniform3fv(rotation_loc, 1, shapes[i]->rotation);
		glUniform3fv(rotation_after_loc, 1, shapes[i]->rotationAfter);
		glUniform1i(overlay_loc, shapes[i]->overlay);
		shapes[i]->render();
	}

	for (unsigned int i = 0; i < noise.size(); i++)
	{
		glUniform4fv(light_position_loc, 1, lights[0]->position);
		glUniform4fv(eye_position_loc, 1, eye);
		glUniform4fv(ambient_product_loc, 1, lights[0]->ambient * noise[i]->material.ambientK);
		glUniform4fv(diffuse_product_loc, 1, lights[0]->diffuse * noise[i]->material.diffuseK);
		glUniform4fv(specular_product_loc, 1, lights[0]->specular * noise[i]->material.specularK);
		glUniform1f(shininess_loc, noise[i]->material.shininess);
		glUniform3fv(scale_loc, 1, noise[i]->scale);
		glUniform3fv(translation_loc, 1, noise[i]->translation);
		glUniform3fv(rotation_loc, 1, noise[i]->rotation);
		glUniform3fv(rotation_after_loc, 1, noise[i]->rotationAfter);
		glUniform1i(overlay_loc, noise[i]->overlay);
		noise[i]->render();
	}
}

GLFWwindow *window;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mv = LookAt(eye, at, up);
	glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, mv);
	renderAll();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// void redisplay(int unused)
// {
// 	glutPostRedisplay();
// 	glutTimerFunc(16, redisplay, 0);
// }

void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));
	if (!glfwInit())
	{
		cerr << "Failed to init glfw" << endl;
	}
	// if (fullScreen)
	// {
	// 	WindowHeight = (GLfloat)glutGet(GLUT_SCREEN_HEIGHT);
	// 	WindowWidth = (GLfloat)glutGet(GLUT_SCREEN_WIDTH);
	// }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(WindowWidth, WindowHeight, "My Title", NULL, NULL);
	if (!window)
	{
		cerr << "Failed to create window" << endl;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE | GLUT_3_2_CORE_PROFILE);
	// glutInitWindowSize((int)(WindowWidth), (int)WindowHeight);
	// glutCreateWindow("Rubik's Cube");

	// if (fullScreen)
	// 	glutFullScreen();

	// int width, height;
	// glfwGetFramebufferSize(window, &WindowWidth, &WindowHeight);

	// glutDisplayFunc(display);
	// glutKeyboardFunc(keyboard);
	// glutSpecialFunc(special);
	// glutTimerFunc(16, redisplay, 0);
	// glLineWidth(1);
	init();
	// #ifdef __APPLE__
	// 	while (!glfwWindowShouldClose(window))
	// 	{
	// 		display();
	// 	}
	// #else
	display();
	emscripten_set_main_loop(display, 0, 1);
	// #endif

	// glutTimerFunc(10, floatView, 0);
	// glutMouseFunc(mouse);
	// glutMainLoop();

	glfwDestroyWindow(window);
	cleanup();
	glfwTerminate();
	return 0;
}
