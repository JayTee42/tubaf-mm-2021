#ifndef GLCALLS_H
#define GLCALLS_H

// Include the GLAD loader *before* including GLFW!
#include "glad/glad.h"

// Include the GLFW library (should be the same for all OS):
#include <GLFW/glfw3.h>

typedef struct
{
	// Dimensions of the window:
	int window_width;
	int window_height;

	// The current shader program:
	GLuint shader_program;

	// The uniforms:
	GLint position_uniform;
	GLint half_frame_uniform;

	// The vertex array object (blackbox ...):
	GLuint vao;

	// The vertex buffer object (GPU mem for the vertex data):
	GLuint vbo;

	// The current cursor position:
	double cursor_position[2];

	// Are we currently panning?
	int is_panning;

	// The position of the window center in the Gaussian plane:
	double position[2];

	// The scale (number of pixels per Gaussian unit):
	double scale;
} user_data_t;

typedef struct
{
	GLfloat position[3];
} vertex_data_t;

// Vertex attributes:
#define ATTRIB_POSITION 0

// Generic error checks:
void check_error(int condition, const char* error_text);
void gl_check_error(const char* error_text);

// GL functions:
void init_gl(GLFWwindow* window);
void draw_gl(GLFWwindow* window);
void teardown_gl(GLFWwindow* window);

#define MIN_SCALE 75.0
#define MAX_SCALE 100000000.0
#define MIN_POSITION -3.0
#define MAX_POSITION 3.0
#define MOUSE_WHEEL_FACTOR 0.25

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif
