/******************************************************************************
 * This is the start of the MIRAGE Game Engine, the idea is to create a RayCast
 * basic engine to make DOOM/Wolfeinstain3D like games.
 *
 * btw the clangd is automatically formatting my code with 2 spaces.
 *****************************************************************************/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "../lib/internal/renderer/renderer.h"
#include "../lib/internal/types/vector.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "MIRAGE_BLANK_BUFFER_0 [FPS = %.0f]"

int main() {
  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "FAILED TO INTIALIZE INTERNAL GLFW WINDOW\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "FAILED TO INTIALIZE INTERNAL GLEW WINDOW\n");
    return 2;
  }

  init_renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

  char title[255];
  float last_frame = 0.f;
  while (!glfwWindowShouldClose(window)) {
    float current_frame = glfwGetTime();
    float frame_delta = current_frame - last_frame;
    last_frame = current_frame;

    glfwPollEvents();
    snprintf(title, 255, WINDOW_TITLE, 1.f / frame_delta);
    glfwSetWindowTitle(window, title);

    clear_screen();
    renderer_draw_point(
        (vec2_t){
            100.f,
            100.f,
        },
        5.f,
        (vec4_t){
            1.f,
            1.f,
            1.f,
            1.f,
        });
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
