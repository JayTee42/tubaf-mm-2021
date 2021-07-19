#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	user_data->window_width = width;
	user_data->window_height = height;
}

double clamp_position(double v)
{
	return MIN(MAX(v, MIN_POSITION), MAX_POSITION);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Get the user data:
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	// Are we currently panning?
	if (user_data->is_panning)
	{
		user_data->position[0] = clamp_position(user_data->position[0] - (xpos - user_data->cursor_position[0]) / user_data->scale);
		user_data->position[1] = clamp_position(user_data->position[1] + (ypos - user_data->cursor_position[1]) / user_data->scale);
	}

	// Save the new cursor position:
	user_data->cursor_position[0] = xpos;
	user_data->cursor_position[1] = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mod)
{
	// Get the user data:
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	// Start / Stop panning:
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		user_data->is_panning = (action == GLFW_PRESS);
	}
}

double clamp_scale(double v)
{
	return MIN(MAX(v, MIN_SCALE), MAX_SCALE);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Get the user data:
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	user_data->scale = clamp_scale(pow(2, MOUSE_WHEEL_FACTOR * yoffset) * user_data->scale);
}

int main(void)
{
	printf("Hello mandelbrot!\n");

	// Create our user data struct:
	user_data_t user_data =
	{
		.window_width = 800,
		.window_height = 600,
		.cursor_position[0] = 0,
		.cursor_position[1] = 0,
		.is_panning = 0,
		.position[0] = 0,
		.position[1] = 0,
		.scale = MIN_SCALE,
	};

	// Specify our error callback func:
	// Then initialize GLFW itself.
	printf("Initializing GLFW ...\n");

	glfwSetErrorCallback(error_callback);
	check_error(glfwInit(), "Failed to initialize GLFW.");

	// We want at least OpenGL 4.1:
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Enable forward-compatibility and use the core profile:
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window:
	printf("Creating window ...\n");

	GLFWwindow* window = glfwCreateWindow(user_data.window_width, user_data.window_height, "Hello triangle", NULL, NULL);
	check_error(window != NULL, "Failed to create window.");

	// Make the OpenGL context of the window the current one:
	glfwMakeContextCurrent(window);

	// Loader function:
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Try to swap on every screen update:
	glfwSwapInterval(1);

	// Specify remaining callbacks:
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Store a pointer to our user data inside the window:
	glfwSetWindowUserPointer(window, &user_data);

	// Initialize everything related to OpenGL:
	init_gl(window);

	while (!glfwWindowShouldClose(window))
	{
		// Draw the next frame:
		draw_gl(window);

		// Swap the buffers to avoid tearing:
		glfwSwapBuffers(window);

		// React to the window manager's messages (e.g. close button):
		glfwPollEvents();
	}

	// Deinitialize the OpenGL stuff:
	teardown_gl(window);

	// Destroy the window:
	glfwDestroyWindow(window);

	// Terminate GLFW:
	glfwTerminate();

	return 0;
}
