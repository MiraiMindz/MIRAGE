/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main render logic of the game engine, like:
 *  - Drawing
 *  - Transformation
 *  - Shaders
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#include "../../../../internal/types/types.h"
#include "../../../../internal/opengl/renderer.h"
#include "../../../../internal/opengl/colors.h"
#include "../../../../internal/opengl/shaders.h"
#include "../../../../internal/opengl/shaders.h"
#include "../../../../internal/ecglm/matrix.h"
#include "cglm/affine.h"
#include "cglm/types.h"

#include <cglm/affine-pre.h>
#include <cglm/mat4.h>
#include <math.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <cglm/cglm.h>


static void init_shader();
static void init_quad();
static void init_projection();

const str vertex_source = "#version 330 core\n"
    "layout(location = 0) in vec2 pos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * model  * vec4(pos, 0.0, 1.0);\n"
    "}\n";

const str fragment_source = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "uniform vec4 color;\n"
    "void main() {\n"
    "   fragColor = color;\n"
    "}\n";

static u16 width, height;
static GLuint program;
static GLuint model_location;
static GLuint color_location;

SDL_GLContext initialize_opengl(SDL_Window* window) {
    // Create an OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    return glContext;
}

void init_renderer(u16 w, u16 h) {
    glClearColor(RGBA_ANSI_COLOR_GREY23_A100);
    width = w;
    height = h;

    init_quad();
    init_shader();
    init_projection();
}

void clear_renderer() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_point(vec2 point, f32 size, vec4 color) {
    mat4 translation;
    mat4f model;

    glm_mat4_identity(translation);
    glm_translate(translation, (vec3){point[0], point[1], 0});
    glm_scale(translation, (vec3){size, size, 1.f});

    eglm_mat4_flatten(translation, model);
    glUniform4fv(color_location, 1, color);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void draw_line(vec2 start, vec2 end, f32 line_width, vec4 color) {
    // Calculate the length of the line (distance between start and end points)
    f32 line_x = end[0] - start[0];
    f32 line_y = end[1] - start[1];
    f32 length = sqrtf((line_x * line_x) + (line_y * line_y));  // Length of the line
    f32 angle = atan2f(line_y, line_x);  // Angle of the line

    // Prepare model matrix
    mat4 translation;
    mat4f model;

    // Identity matrix initialization
    glm_mat4_identity(translation);

    // Translate to the midpoint of the line
    glm_translate(translation, (vec3){(start[0] + end[0]) / 2.f, (start[1] + end[1]) / 2.f, 0});

    // Rotate by the calculated angle
    glm_rotate_z(translation, angle, translation);

    // Scale the line by its length (along the X-axis) and its width (Y-axis)
    glm_scale(translation, (vec3){length, line_width, 1.f});

    // Flatten and send the model matrix to the shader
    eglm_mat4_flatten(translation, model);
    glUniform4fv(color_location, 1, color);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

    // Draw the line (quad)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}


void draw_quad(vec2 center, vec2 size,f32 angle, vec4 color) {
    mat4 translation;
    mat4f model;

    glm_mat4_identity(translation);
    glm_translate(translation, (vec3){center[0], center[1], 0});
    glm_scale(translation, (vec3){size[0], size[1], 1.f});
    glm_rotate_z(translation, angle, translation);

    eglm_mat4_flatten(translation, model);
    glUniform4fv(color_location, 1, color);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, model);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

static void init_shader() {
    GLuint vertex = compile_shaders(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment = compile_shaders(GL_FRAGMENT_SHADER, fragment_source);
    program = link_program(2, vertex, fragment);

    glUseProgram(program);
    model_location = glGetUniformLocation(program, "model");
    color_location = glGetUniformLocation(program, "color");
}

static void init_quad() {
    // This will be the vertices of your quad.
    // the origin (0, 0) is on the middle, so:
    //      +x = right
    //      -x = left
    //      +y = top
    //      -y = bottom
    // our quad will be 1 unit in size
    f32 vertices[] = {
    //   X       Y
        .5f,    .5f,   // top-right
        .5f,   -.5f,   // bottom-right
       -.5f,    .5f,   // top-left
       -.5f,   -.5f,   // bottom-left
    };

    u32 indices[] = {
        0, 1, 3, 
        0, 2, 3,
    };

    GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &element_buffer_object);

    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unbind only vertex_buffer_object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void init_projection() {
    mat4 projection;
    mat4f flat_projection;
    glm_ortho(0.f, (f32)width, (f32)height, 0.f, -1.f, 1.f, projection);
    GLuint projection_location = glGetUniformLocation(program, "projection");
    eglm_mat4_flatten(projection, flat_projection);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, flat_projection);
}
