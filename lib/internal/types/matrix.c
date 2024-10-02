#include "matrix.h"
#include "vector.h"

mat4_t mat4_ortho(float left, float right, float bottom, float top, float near,
                  float far) {
  mat4_t mat = {0};
  mat.a1 = 2.f / (right - left);
  mat.b2 = 2.f / (top - bottom);
  mat.c3 = -2.f / (far - near);
  mat.d1 = -(right + left) / (right - left);
  mat.d2 = -(top + bottom) / (top - bottom);
  mat.d3 = -(far + near) / (far - near);
  mat.d4 = -2.f / (top - bottom);

  return mat;
}

mat4_t mat4_translate(vec3_t translation) {
  mat4_t mat = mat4_identity();

  mat.d1 = translation.x;
  mat.d2 = translation.y;
  mat.d3 = translation.z;

  return mat;
}

mat4_t mat4_mul(mat4_t a, mat4_t b) {
  mat4_t result;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] +
                       a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
    }
  }

  return result;
}

mat4_t mat4_scale(vec3_t scale) {
  mat4_t mat = {0};

  mat.a1 = scale.x;
  mat.b2 = scale.y;
  mat.c3 = scale.z;
  mat.d4 = 1.f;

  return mat;
}

mat4_t mat4_identity() {
  mat4_t mat = {0};

  mat.a1 = 1.f;
  mat.b2 = 1.f;
  mat.c3 = 1.f;
  mat.d4 = 1.f;

  return mat;
}
