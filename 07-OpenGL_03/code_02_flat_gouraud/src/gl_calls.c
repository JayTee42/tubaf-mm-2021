#include "gl_calls.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "obj.h"

#define MODEL_PATH "../models/teapot"
#define Y_ANGULAR_VELOCITY 2

static char* read_shader_source_from_file(const char* path)
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

    // Read and specify the source code:
    char* shader_source = read_shader_source_from_file(shader_path);

    glShaderSource(shader, 1, (const char**)&shader_source, NULL);
    gl_check_error("glShaderSource");

    free(shader_source);

    // Compile the shader:
    glCompileShader(shader);
    gl_check_error("glCompileShader");

    // Check the compilation status:
    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    gl_check_error("glGetShaderiv");

    if (success)
    {
        return shader;
    }

    // Extract the length of the error message (including '\0'):
    GLint info_length = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
    gl_check_error("glGetShaderiv");

    if (info_length > 1)
    {
        // Extract the message itself:
        char* info = malloc(info_length);
        check_error(info != NULL, "Failed to allocate memory for error message.");

        glGetShaderInfoLog(shader, info_length, NULL, info);
        gl_check_error("glGetShaderInfoLog");

        fprintf(stderr, "Error compiling shader (%s): %s\n", shader_tag, info);
        free(info);
    }
    else
    {
        fprintf(stderr, "No info log from the shader compiler :(\n");
    }

    exit(EXIT_FAILURE);
}

static void init_shader_program(user_data_t* user_data)
{
    // Create the vertex shader:
    printf("Compiling vertex shader ...\n");
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, "shader/vertex.glsl", "Vertex shader");

    // Create the fragment shader:
    printf("Compiling fragment shader ...\n");
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, "shader/fragment.glsl", "Fragment shader");

    // Create an empty shader program:
    printf("Creating shader program ...\n");

    GLuint shader_program = glCreateProgram();
    gl_check_error("glCreateProgram");

    // Attach both shaders to the program:
    glAttachShader(shader_program, vertex_shader);
    gl_check_error("glAttachShader [vertex]");

    glAttachShader(shader_program, fragment_shader);
    gl_check_error("glAttachShader [fragment]");

    // Link the shader program:
    glLinkProgram(shader_program);
    gl_check_error("glLinkProgram");

    // Detach the shaders after linking:
    glDetachShader(shader_program, vertex_shader);
    gl_check_error("glDetachShader [vertex]");

    glDetachShader(shader_program, fragment_shader);
    gl_check_error("glDetachShader [fragment]");

    // Delete the shaders:
    glDeleteShader(vertex_shader);
    gl_check_error("glDeleteShader [vertex]");

    glDeleteShader(fragment_shader);
    gl_check_error("glDeleteShader [fragment]");

    // Check the link status:
    GLint success;

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    gl_check_error("glGetProgramiv");

    if (success)
    {
        // Use the program from now on:
        glUseProgram(shader_program);
        gl_check_error("glUseProgram");

        // Store it inside our user data struct:
        user_data->shader_program = shader_program;

        // We can now release the shader compiler.
        glReleaseShaderCompiler();
        gl_check_error("glReleaseShaderCompiler");

        return;
    }

    // Extract the length of the error message (including '\0'):
    GLint info_length = 0;
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_length);
    gl_check_error("glGetProgramiv");

    if (info_length > 1)
    {
        // Extract the message itself:
        char* info = malloc(info_length);
        check_error(info != NULL, "Failed to allocate memory for error message.");

        glGetProgramInfoLog(shader_program, info_length, NULL, info);
        gl_check_error("glGetProgramInfoLog");

        fprintf(stderr, "Error linking shader program: %s\n", info);
        free(info);
    }
    else
    {
        fprintf(stderr, "No info log from the shader compiler :(\n");
    }

    exit(EXIT_FAILURE);
}

static void init_uniforms(user_data_t* user_data)
{
    user_data->angle_y_loc = glGetUniformLocation(user_data->shader_program, "angle_y");

    gl_check_error("glGetUniformLocation [angle_y]");
    check_error(user_data->angle_y_loc >= 0, "Failed to obtain uniform location for angle_y.");
}

static void init_vertex_data(user_data_t* user_data)
{
    // Blackbox! Create a VAO.
    GLuint vao;

    glGenVertexArrays(1, &vao);
    gl_check_error("glGenVertexArrays");

    glBindVertexArray(vao);
    gl_check_error("glBindVertexArray");

    // Store the VAO inside our user data:
    user_data->vao = vao;

    // Generate and bind a vertex buffer object:
    GLuint vbo;

    glGenBuffers(1, &vbo);
    gl_check_error("glGenBuffers");

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    gl_check_error("glBindBuffer");

    // Open the obj file:
    FILE* obj = fopen(MODEL_PATH, "r");
    check_error(obj != NULL, "Failed to open obj file at \"" MODEL_PATH "\".");

    // Count the entries:
    int vertex_count = 0;
    int tex_coords_count = 0;
    int normal_count = 0;
    int face_count = 0;
    int mtl_lib_count = 0;

    obj_count_entries(obj, &vertex_count, &tex_coords_count, &normal_count, &face_count, &mtl_lib_count);

    printf("Parsed obj file \"%s\":\n", MODEL_PATH);
    printf("\tVertices: %d\n", vertex_count);
    printf("\tTexture coordinates: %d\n", tex_coords_count);
    printf("\tNormals: %d\n", normal_count);
    printf("\tFaces: %d\n", face_count);
    printf("\tMaterial libraries: %d\n", mtl_lib_count);

    // Rewind the file pointer:
    rewind(obj);

    // - one array for the obj vertices
    obj_vertex_entry_t *vertices = malloc(sizeof(obj_vertex_entry_t) * vertex_count);
    check_error(vertices != NULL, "Failed to allocate memory for vertices.");

    // - one array for the obj tex coords
    obj_tex_coords_entry_t *tex_coords = malloc(sizeof(obj_tex_coords_entry_t) * tex_coords_count);
    check_error(tex_coords != NULL, "Failed to allocate memory for tex coordinates.");

    // - one array for the obj normals
    obj_normal_entry_t *normals = malloc(sizeof(obj_normal_entry_t) * normal_count);
    check_error(normals != NULL, "Failed to allocate memory for normals.");

    // - one array for the vertex data structs (built from the faces)
    vertex_data_t *vertex_data = malloc(sizeof(vertex_data_t) * face_count * 3);
    check_error(vertex_data != NULL, "Failed to allocate memory for vertex data.");

    obj_entry_type_t entry_type;
    obj_entry_t entry;

    size_t vertex_index = 0;
    size_t tex_coord_index = 0;
    size_t normal_index = 0;
    size_t vertex_data_index = 0;

    // TODO: Clean index validation!
    while ((entry_type = obj_get_next_entry(obj, &entry)) != OBJ_ENTRY_TYPE_END)
    {
        switch (entry_type)
        {
            case OBJ_ENTRY_TYPE_VERTEX: vertices[vertex_index++] = entry.vertex_entry; break;
            case OBJ_ENTRY_TYPE_TEX_COORDS: tex_coords[tex_coord_index++] = entry.tex_coords_entry; break;
            case OBJ_ENTRY_TYPE_NORMAL: normals[normal_index++] = entry.normal_entry; break;

            case OBJ_ENTRY_TYPE_FACE:

                for (size_t i = 0; i < 3; i++)
                {
                    const obj_vertex_entry_t* vertex = &vertices[entry.face_entry.triples[i].vertex_index];
                    const obj_normal_entry_t* normal = &normals[entry.face_entry.triples[i].normal_index];

                    vertex_data[vertex_data_index++] = (vertex_data_t)
                    {
                        .position = { vertex->x, vertex->y, vertex->z },
                        .color = { 0x80, 0x80, 0x80 },
                        .normal = { normal->x, normal->y, normal->z }
                    };
                }

                break;

            default: break;
        }
    }
    user_data->vertex_data_count = face_count * 3;

    // Upload the data to the GPU:
    glBufferData(GL_ARRAY_BUFFER, user_data->vertex_data_count * sizeof(vertex_data_t), (const GLvoid*)vertex_data, GL_STATIC_DRAW);

    fclose(obj);
    free(vertices);
    free(tex_coords);
    free(normals);
    free(vertex_data);

    // Position attribute:
    // Number of attribute, number of components, data type, normalize, stride, pointer (= offset)
    glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data_t), (GLvoid*)offsetof(vertex_data_t, position));
    gl_check_error("glVertexAttribPointer [position]");

    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex_data_t), (GLvoid*)offsetof(vertex_data_t, color));
    gl_check_error("glVertexAttribPointer [color]");

    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data_t), (GLvoid*)offsetof(vertex_data_t, normal));
    gl_check_error("glVertexAttribPointer [normal]");

    // Enable the attributes:
    glEnableVertexAttribArray(ATTRIB_POSITION);
    gl_check_error("glEnableVertexAttribArray [position]");

    glEnableVertexAttribArray(ATTRIB_COLOR);
    gl_check_error("glEnableVertexAttribArray [color]");

    glEnableVertexAttribArray(ATTRIB_NORMAL);
    gl_check_error("glEnableVertexAttribArray [normal]");

    // Store the VBO inside our user data:
    user_data->vbo = vbo;
}

static void init_model(user_data_t* user_data)
{
    user_data->last_frame_time = glfwGetTime();
    user_data->angle_y = 0;
}

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

void init_gl(GLFWwindow* window)
{
    user_data_t* user_data = glfwGetWindowUserPointer(window);

    // Initialize our shader program:
    init_shader_program(user_data);

    // Initialize our uniforms:
    init_uniforms(user_data);

    // Initialize our vertex data:
    init_vertex_data(user_data);

    // Initialize our model:
    init_model(user_data);

    // Obtain the internal size of the framebuffer:
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);

    // Align the viewport to the framebuffer:
    glViewport(0, 0, fb_width, fb_height);
    gl_check_error("glViewport");

    // Specify the clear color:
    glClearColor(0.1, 0.1, 0.1, 1);
    gl_check_error("glClearColor");

    // Enable the depth test:
    glEnable(GL_DEPTH_TEST);
    gl_check_error("glEnable [depth test]");

    // Enable backface culling:
    //glEnable(GL_CULL_FACE);
}

void update_gl(GLFWwindow* window)
{
    user_data_t* user_data = glfwGetWindowUserPointer(window);

    // Calculate the frame delta time and update the timestamp:
    double frame_time = glfwGetTime();
    double delta_time = frame_time - user_data->last_frame_time;

    user_data->last_frame_time = frame_time;

    // TODO: Update the angle.
    user_data->angle_y = fmod(user_data->angle_y + (Y_ANGULAR_VELOCITY * delta_time), 2 * M_PI);

    // Push the uniforms to the GPU:
    glUniform1f(user_data->angle_y_loc, user_data->angle_y);
    gl_check_error("glUniform1f [angle_y]");
}

void draw_gl(GLFWwindow* window)
{
    user_data_t* user_data = glfwGetWindowUserPointer(window);

    // Clear the color buffer -> background color:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_check_error("glClear");

    // Draw our stuff!
    // Parameters: primitive type, start index, count
    glDrawArrays(GL_TRIANGLES, 0, user_data->vertex_data_count);
    gl_check_error("glDrawArrays");
}

void teardown_gl(GLFWwindow* window)
{
    printf("Tearing down ...\n");
    user_data_t* user_data = glfwGetWindowUserPointer(window);

    // Delete the shader program:
    glDeleteProgram(user_data->shader_program);
    gl_check_error("glDeleteProgram");

    // Delete the VAO:
    glDeleteVertexArrays(1, &user_data->vao);
    gl_check_error("glDeleteVertexArrays");

    // Delete the VBO:
    glDeleteBuffers(1, &user_data->vbo);
    gl_check_error("glDeleteBuffers");
}
