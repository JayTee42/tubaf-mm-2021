#ifndef GLCALLS_H
#define GLCALLS_H

// Include the GLAD loader *before* including GLFW!
#include "glad/glad.h"

// Include the GLFW library (should be the same for all OS):
#include <GLFW/glfw3.h>

// TODO
typedef struct
{
    // Dimensions of the window:
    int window_width;
    int window_height;
} user_data_t;

typedef struct
{

} vertex_data_t;

// Generic error checks:
void check_error(int condition, const char* error_text);
void gl_check_error(const char* error_text);

// GL functions:
void init_gl(GLFWwindow* window);
void draw_gl(GLFWwindow* window);
void teardown_gl(GLFWwindow* window);

#endif
