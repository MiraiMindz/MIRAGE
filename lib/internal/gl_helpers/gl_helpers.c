#include "gl_helpers.h"
#include <GL/glew.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

GLuint compile_shader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader, sizeof(info_log), NULL, info_log);
    fprintf(stderr, "FAILED TO COMPILE SHADERS\nLOG:\n%s\n", info_log);
  }

  return shader;
}

GLuint link_program(size_t number_of_shaders, ...) {
  GLuint program = glCreateProgram();

  va_list variable_arguments;
  va_start(variable_arguments, number_of_shaders);
  for (size_t i = 0; i < number_of_shaders; i++) {
    glAttachShader(program, va_arg(variable_arguments, GLuint));
  }
  va_end(variable_arguments);

  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program, sizeof(info_log), NULL, info_log);
    fprintf(stderr, "FAILED TO LINK PROGRAM\nLOG:\n%s\n", info_log);
  }

  return program;
}
