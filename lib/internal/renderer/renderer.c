#include "renderer.h"
#include <GL/glew.h>
#include <stdint.h>

#include "../gl_helpers/gl_helpers.h"
#include "../types/matrix.h"
#include "../types/vector.h"

static void init_shader();
static void init_quad();
static void init_projection();

const char *vertex_source =
    "#version 330 core\n"
    "layout(location = 0) in vec2 pos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
    "}\n";

const char *fragment_source = "#version 330 core\n"
                              "out vec4 fragColor;\n"
                              "uniform vec4 color;\n"
                              "void main() {\n"
                              "   fragColor = color;\n"
                              "}\n";

static float width_g, height_g;
static GLuint program;
static GLuint model_location;

void init_renderer(int width, int height) {
  width_g = width;
  height_g = height;
  glClearColor(0.5f, 0.5f, 0.5f, 1.f);
  init_shader();
  init_quad();
  init_projection();
}

void clear_screen() { glClear(GL_COLOR_BUFFER_BIT); }
void renderer_draw_point(vec2_t point, float size, vec4_t color) {
  mat4_t translation = mat4_translate((vec3_t){point.x, point.y, 0.f});
  mat4_t scale = mat4_scale((vec3_t){size, size, 1.f});
  mat4_t model = mat4_mul(scale, translation);

  glUniformMatrix4fv(model_location, 1, GL_FALSE, model.v);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

static void init_shader() {
  GLuint vertex = compile_shader(GL_VERTEX_SHADER, vertex_source);
  GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
  program = link_program(2, vertex, fragment);

  glUseProgram(program);

  model_location = glGetUniformLocation(program, "model");
}

static void init_quad() {
  float vertices[] = {
      //  X       Y
      0.5f,  0.5f,  // top right
      0.5f,  -0.5f, // bottom right
      -0.5f, -0.5f, // bottom left
      0.5f,  -0.5f, // top left
  };

  uint32_t indices[] = {
      0, 1, 3, // 1st triangle
      1, 2, 3, // 2nd triangle
  };

  GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;
  glGenVertexArrays(1, &vertex_array_object);
  glGenBuffers(1, &vertex_buffer_object);
  glGenBuffers(1, &element_buffer_object);

  glBindVertexArray(vertex_array_object);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void init_projection() {
  mat4_t projection = mat4_ortho(0.f, width_g, height_g, 0.f, -1.f, 1.f);
  GLuint projection_location = glGetUniformLocation(program, "projection");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.v);
}
