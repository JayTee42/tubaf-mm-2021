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

    // The vertex array object (blackbox ...):
    GLuint vao;

    // The vertex buffer object (GPU mem for the vertex data):
    GLuint vbo;

    // The number of vertices to render:
    int vertex_data_count;
} user_data_t;

typedef struct
{
    GLfloat position[3];
    GLubyte color[3];
} vertex_data_t;

// Vertex attributes:
#define ATTRIB_POSITION 0
#define ATTRIB_COLOR 1

// Generic error checks:
void check_error(int condition, const char* error_text);
void gl_check_error(const char* error_text);

// GL functions:
void init_gl(GLFWwindow* window);
void update_gl(GLFWwindow* window);
void draw_gl(GLFWwindow* window);
void teardown_gl(GLFWwindow* window);

#endif
