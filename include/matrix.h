#pragma once

typedef struct matrix {
  int width, height;
  int** content;
} matrix_t;

int mul(matrix_t* a, matrix_t* b, matrix_t* result);
void print_matrix(matrix_t* a);