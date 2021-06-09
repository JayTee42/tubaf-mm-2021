#include "gl_calls.h"

#include <stdio.h>
#include <stdlib.h>

void check_error(int condition, const char* error_text)
{
	if (!condition)
	{
		fprintf(stderr, "%s\n", error_text);
		exit(EXIT_FAILURE);
	}
}

void gl_check_error(const char* error_text)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		fprintf(stderr, "GLError: %s (%d)\n", error_text, error);
		exit(EXIT_FAILURE);
	}
}

static char* string_from_file(const char* path)
{
	// Open the file:
	FILE* file = fopen(path , "rb");
	check_error(file != NULL, "Failed to open file.");

	// Seek to the end:
	int success = fseek(file, 0, SEEK_END);
	check_error(success == 0, "Failed to forward file pointer.");

	// Obtain the size of the file from the position of the file pointer:
	long size = ftell(file);
	check_error(size >= 0, "Failed to determine file size.");

	// Rewind the file pointer back to the start:
	rewind(file);

	// Allocate the output buffer:
	char* buffer = malloc(size + 1);
	check_error(buffer != NULL, "Failed to allocate buffer.");

	// Read into it:
	size_t blocks_read = fread(buffer, size, 1, file);
	check_error(blocks_read == 1, "Failed to read file.");

	// Close the file:
	success = fclose(file);
	check_error(success == 0, "Failed to close file.");

	// Append a null-terminator and return the buffer:
	buffer[size] = '\0';

	return buffer;
}

static GLuint compile_shader(GLenum type, const char* shader_path, const char* shader_tag)
{
	// Create an empty shader:
	GLuint shader = glCreateShader(type);
	gl_check_error("glCreateShader");

	// Read the specific source:
	char* shader_source = string_from_file(shader_path);

	glShaderSource(shader, 1, (const char**)&shader_source, NULL);
	gl_check_error("glShaderSource");

	free(shader_source);

	// Compile the shader:
	glCompileShader(shader);
	gl_check_error("glCompileShader");

	// Check the compile status:
	GLint success;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	gl_check_error("glGetShaderiv");

	if (success)
	{
		return shader;
	}
	
	// Extract the length of the error message (incl. '\0')
	GLint info_length = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);

	if (info_length > 1)
	{
		// Extract the error message:
		char* info = malloc(info_length);
		check_error(info != NULL, "Failed to alloc memory for error message :(");

		glGetShaderInfoLog(shader, info_length, NULL, info);
		gl_check_error("glGetShaderInfoLog");

		fprintf(stderr, "Error compiling shader (%s): %s", shader_tag, info);
		free(info);
	}
	else
	{
		fprintf(stderr, "No info log from the shader compiler :(");
	}
	
	exit(EXIT_FAILURE);
}

static void init_shader_program(user_data_t* user_data)
{

}

static void init_vertex_data(user_data_t* user_data)
{
	// TODO
}

void init_gl(GLFWwindow* window)
{
	user_data_t* user_data = glfwGetWindowUserPointer(window);

	// Init our shader program:
	init_shader_program(user_data);

	// Init our vertex data:
	init_vertex_data(user_data);

	// Obtain the internal size of the framebuffer
	int fb_width, fb_height;
	glfwGetFramebufferSize(window, &fb_width, &fb_height);

	// Align the viewport according to the framebuffer:
	glViewport(0,0,fb_width, fb_height);
	gl_check_error("glVieport");

	// Specify the clear color:
	glClearColor(0.1, 0.1, 0.4, 1);
	gl_check_error("glClearColor");
}

void draw_gl(GLFWwindow* window)
{
	// Clear the color buffer -> background color:
	glClear(GL_COLOR_BUFFER_BIT);
	gl_check_error("glClear");
}

void teardown_gl(GLFWwindow* window)
{
	// TODO
}
