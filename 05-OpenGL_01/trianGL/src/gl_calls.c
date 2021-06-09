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
	// Create the vertex shader:
	GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER,"shader/vertex.glsl", "Vertex Shader");

	// Create the fragment shader:
	GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, "shader/fragment.glsl", "Fragment Shader");

	// We can now release the shader compiler:
	glReleaseShaderCompiler();
	gl_check_error("glReleaseShaderCompiler");

	// Create an empty shader object:
	GLuint shader_program = glCreateProgram();
	gl_check_error("glCreateProgram");

	// Attach both shaders to program:
	glAttachShader(shader_program, vertex_shader);
	gl_check_error("glAttachShader(vertex)");
	
	glAttachShader(shader_program, fragment_shader);
	gl_check_error("glAttachShader(fragment)");

	// Link shader program:
	glLinkProgram(shader_program);
	gl_check_error("glLinkProgram");

	// Detach both shaders to program:
	glDetachShader(shader_program, vertex_shader);
	gl_check_error("glDetachShader(vertex)");
	
	glDetachShader(shader_program, fragment_shader);
	gl_check_error("glDetachShader(fragment)");

	// Delete the shaders:
	glDeleteShader(vertex_shader);
	gl_check_error("glDeleteShader(vertex_shader)");

	glDeleteShader(fragment_shader);
	gl_check_error("glDeleteShader(fragment_shader)");

		// Check the compile status:
	GLint success;

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	gl_check_error("glGetProgramiv");

	if (success)
	{
		// Use the program from now on:
		glUseProgram(shader_program);
		gl_check_error("glUseProgram");

		// Store the program handle inside the user data:
		user_data->shader_program = shader_program;

		return;
	}
	
	// Extract the length of the error message (incl. '\0')
	GLint info_length = 0;

	glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_length);

	if (info_length > 1)
	{
		// Extract the error message:
		char* info = malloc(info_length);
		check_error(info != NULL, "Failed to alloc memory for error message :(");

		glGetProgramInfoLog(shader_program, info_length, NULL, info);
		gl_check_error("glGetProgramInfoLog");

		fprintf(stderr, "Error linking shader: %s", info);
		free(info);
	}
	else
	{
		fprintf(stderr, "No info log from the shader linker :(");
	}
	
	exit(EXIT_FAILURE);
}

static void init_vertex_data(user_data_t* user_data)
{
	// Triangle data:
	vertex_data_t vertex_data[] = 
	{
		{.position = {-1, -1, 0}, .color = { 0xFF, 0x00, 0x00 } }, // left bottom
		{.position = { 1, -1, 0}, .color = { 0x00, 0xFF, 0x00 } }, // right bottom
		{.position = { 0,  1, 0}, .color = { 0x00, 0x00, 0xFF } }, // left bottom
	};

	// Create a Vertex Array Object VAO:
	GLuint vao;

	glGenVertexArrays(1, &vao);
	gl_check_error("glGenVertexArrays");

	glBindVertexArray(vao);
	gl_check_error("glBindVertexArray");

	// Store the VAO inside our user data:
	user_data->vao = vao;

	// Generate and bind the Vertex Buffer Object:
	GLuint vbo;

	glGenBuffers(1, &vbo);
	gl_check_error("glGenBuffers");

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	gl_check_error("glBindBuffer");

	// Upload the vertex data to the GPU:
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex_data_t), (const GLvoid*)vertex_data, GL_STATIC_DRAW);
	gl_check_error("glBufferData");

	// Position attribute:
	// 
	glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data_t), (GLvoid*)offsetof(vertex_data_t, position));
	gl_check_error("glVertexAttribPointer(ATTRIB_POSITION)");

	// Color attribute:
	glVertexAttribPointer(ATTRIB_COLOR, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex_data_t), (GLvoid*)offsetof(vertex_data_t, color));
	gl_check_error("glVertexAttribPointer(ATTRIB_COLOR)");

	// Enable the attributes:
	glEnableVertexAttribArray(ATTRIB_POSITION);
	gl_check_error("glEnableVertexAttribArray(ATTRIB_POSITION)");

	glEnableVertexAttribArray(ATTRIB_COLOR);
	gl_check_error("glEnableVertexAttribArray(ATTRIB_COLOR)");

	// Store vbo handle inside our user data:
	user_data->vbo = vbo;
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
