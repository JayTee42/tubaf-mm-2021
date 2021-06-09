#include <stdio.h>
#include <stdlib.h>

#include "gl_calls.h"

// Very naughty hack to fix a Cygwin linker error when using the MinGW GLFW binaries ... :(
#ifdef __CYGWIN__
	#include <stdarg.h>

	void __ms_vsnprintf(char * s, size_t n, const char * format, va_list arg)
	{
		vsnprintf(s, n, format, arg);
	}
#endif

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s (%d)\n", description, error);
	exit(EXIT_FAILURE);
}

void framebuffer_size_callback(GLFWwindow* window, int fb_width, int fb_height)
{
	glViewport(0, 0, fb_width, fb_height);
	gl_check_error("glViewport");
	//printf("FrameBufferSize: %dx%d\n", fb_width, fb_height);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	user_data->window_width = width;
	user_data->window_height = height;

	//printf("WindowSize: %dx%d\n", width, height);
}

int main(void)
{
	printf("Hello triangle!\n");
	
	// Create our data struct:
	user_data_t user_data =
	{
		.window_width=800,
		.window_height=600
	};

	printf("Initializing GLFW...\n");

	// Specify our error callback function:
	glfwSetErrorCallback(error_callback);

	// Init GLFW:
	check_error(glfwInit(), "Failed to initialize GLFW :(");

	// We want at least OpenGL version 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Enable forward-compatibilty and use the core profile:
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window
	printf("Creating the window... \n");

	GLFWwindow* window = glfwCreateWindow(
							user_data.window_width,
							user_data.window_height,
							"Hello triangle", NULL, NULL);
	check_error(window != NULL, "Failed to create window... :(");

	// Make the OpenGL context of the window the current one:
	glfwMakeContextCurrent(window);

	// GLAD loader function:
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Try to swap every frame:
	glfwSwapInterval(1);

	// Specify the remaining callbacks:
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	// Store the user data inside the window:
	glfwSetWindowUserPointer(window, &user_data);

	// Init everything related to OpenGL:
	init_gl(window);

	while(!glfwWindowShouldClose(window))
	{
		// Draw a frame:
		draw_gl(window);

		// Swap the buffer to avoid tearing
		glfwSwapBuffers(window);

		// React to the window manager's messages (e.g. close button)
		glfwPollEvents();
	}

	// Deinit the OpenGL stuff:
	teardown_gl(window);

	// Destroy the window:
	glfwDestroyWindow(window);

	// Terminate GLFW:
	glfwTerminate();

	return 0;
}
