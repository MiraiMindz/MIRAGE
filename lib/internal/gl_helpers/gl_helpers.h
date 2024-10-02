#ifndef _GL_HELPERS_H
#define _GL_HELPERS_H

#include <GL/glew.h>
#include <stdarg.h>
#include <stddef.h>

GLuint compile_shader(GLenum type, const char *source);
GLuint link_program(size_t number_of_shaders, ...);

#endif
