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

#include "../../../../internal/opengl/renderer.h"
#include "../../../../internal/ecglm/matrix.h"
#include "../../../../internal/opengl/colors.h"
#include "../../../../internal/opengl/shaders.h"
#include "../../../../internal/types/types.h"
#include "../../../emath/emath.h"
#include "../../../opengl/mesh.h"

#include <SDL2/SDL.h>
#include <cglm/cglm.h>
#include <math.h>
#include <stddef.h>

// This function initializes the shader (currently only one)
static void init_shader();

// This function initializes the drawing of a quad into the GPU
static void init_quad();

// This function initializes the orthographic projection
static void init_projection();

// We are currently defining the shaders sources here, but there is a plan
// to load .glsl files.
const str vertex_source =
    "#version 330 core\n"
    "layout(location = 0) in vec2 pos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "void main() {\n"
    "   gl_Position = projection * view * model  * vec4(pos, 0.0, 1.0);\n"
    "}\n";

const str fragment_source = "#version 330 core\n"
                            "out vec4 fragColor;\n"
                            "uniform vec4 color;\n"
                            "void main() {\n"
                            "   fragColor = color;\n"
                            "}\n";

static u16 width, height;
static GLuint program;
static GLuint model_location, view_location, projection_location;
static GLuint color_location;

static mesh_t quad_mesh;

// This function initializes the OpenGL Context
SDL_GLContext initialize_opengl(SDL_Window *window) {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n",
                SDL_GetError());
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

// This function initializes the OpenGL Renderer
void init_renderer(u16 w, u16 h) {
    glClearColor(RGBA_ANSI_COLOR_GREY23_A100);
    width = w;
    height = h;

    init_quad();
    init_shader();
    init_projection();
}

// This function clears the OpenGL Renderer
void clear_renderer() { glClear(GL_COLOR_BUFFER_BIT); }

// Allows the program to set the view matrix
void set_view(mat4f view) {
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
}

void set_projection(mat4f projection) {
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection);
}

// This function draws an arbitrary mesh into the screen given it's
// transformation and color
void draw_mesh(const mesh_t *mesh, mat4f transformation, vec4 color) {
    glUniform4fv(color_location, 1, color);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, transformation);
    glBindVertexArray(mesh->vertex_array_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer_object);
    glDrawElements(GL_TRIANGLES, mesh->number_of_indices, GL_UNSIGNED_INT,
                   NULL);
}

// This function draws an arbitrary point into the screen given it's coordinates
// and color
void draw_point(vec2 point, f32 size, vec4 color) {
    mat4 translation;
    mat4f model;

    glm_mat4_identity(translation);
    glm_translate(translation, (vec3){point[0], point[1], 0});
    glm_scale(translation, (vec3){size, size, 1.f});

    eglm_mat4_flatten(translation, model);

    draw_mesh(&quad_mesh, model, color);
}

// This function draws an arbitrary line into the screen given it's coordinates
// width and color
void draw_line(vec2 start, vec2 end, f32 line_width, vec4 color) {
    // Calculate the length of the line (distance between start and end points)
    f32 line_x = end[0] - start[0];
    f32 line_y = end[1] - start[1];
    f32 length =
        sqrtf((line_x * line_x) + (line_y * line_y)); // Length of the line
    f32 angle = atan2f(line_y, line_x);               // Angle of the line

    // Prepare model matrix
    mat4 translation;
    mat4f model;

    // Identity matrix initialization
    glm_mat4_identity(translation);

    // Translate to the midpoint of the line
    glm_translate(translation, (vec3){(start[0] + end[0]) / 2.f,
                                      (start[1] + end[1]) / 2.f, 0});

    // Rotate by the calculated angle
    glm_rotate_z(translation, angle, translation);

    // Scale the line by its length (along the X-axis) and its width (Y-axis)
    glm_scale(translation, (vec3){length, line_width, 1.f});

    // Flatten and send the model matrix to the shader
    eglm_mat4_flatten(translation, model);

    draw_mesh(&quad_mesh, model, color);
}

// This function draws an arbitrary quad into the screen given it's coordinates
// size and color
void draw_quad(vec2 center, vec2 size, f32 angle, vec4 color) {
    mat4 translation;
    mat4f model;

    glm_mat4_identity(translation);
    glm_translate(translation, (vec3){center[0], center[1], 0});
    glm_scale(translation, (vec3){size[0], size[1], 1.f});
    glm_rotate_z(translation, angle, translation);

    eglm_mat4_flatten(translation, model);
    draw_mesh(&quad_mesh, model, color);
}

// This function initializes the shader (currently only one)
static void init_shader() {
    GLuint vertex = compile_shaders(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment = compile_shaders(GL_FRAGMENT_SHADER, fragment_source);
    program = link_program(2, vertex, fragment);

    glUseProgram(program);
    projection_location = glGetUniformLocation(program, "projection");
    model_location = glGetUniformLocation(program, "model");
    view_location = glGetUniformLocation(program, "view");
    color_location = glGetUniformLocation(program, "color");
}

// This function initializes the drawing of a quad into the GPU
static void init_quad() {
    // This will be the vertices of our quad.
    // the origin (0, 0) is on the middle, so:
    //      +x = right
    //      -x = left
    //      +y = top
    //      -y = bottom
    // our quad will be 1 unit in size
    vertex_t vertices[] = {
        //   X       Y      Z
        {.position = {.5f, .5f, 0.f}},   // top-right
        {.position = {.5f, -.5f, 0.f}},  // bottom-right
        {.position = {-.5f, .5f, 0.f}},  // top-left
        {.position = {-.5f, -.5f, 0.f}}, // bottom-left
    };

    u32 indices[] = {
        0, 1, 3, 0, 2, 3,
    };

    create_mesh(&quad_mesh, 4, vertices, 6, indices);

    // unbind only vertex_buffer_object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// This function initializes the orthographic projection
static void init_projection() {
    mat4 projection;
    mat4f flat_projection;

    glm_ortho(0.f, (f32)width, (f32)height, 0.f, -1.f, 1.f, projection);
    GLuint glprojection_location = glGetUniformLocation(program, "projection");
    eglm_mat4_flatten(projection, flat_projection);
    glUniformMatrix4fv(glprojection_location, 1, GL_FALSE, flat_projection);

    // PLACEHOLDER FOR THE VIEW PROJECTION
    mat4f flat_identity_mat;
    mat4 identity_mat;
    glm_mat4_identity(identity_mat);
    eglm_mat4_flatten(identity_mat, flat_identity_mat);
    set_view(flat_identity_mat);
}

f32 get_width() { return width; }
f32 get_height() { return height; }
void get_dimensions(vec2 dest) {
    dest[0] = width;
    dest[1] = height;
}
