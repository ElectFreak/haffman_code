#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

static int mul_vectors(matrix_t* a, matrix_t* b, int i, int j) {
  int sum = 0;
  for (int pos = 0; pos < a->width; pos++)
    sum += a->content[i][pos] * b->content[pos][j];
  
  return sum % 2;
}

int mul(matrix_t* a, matrix_t* b, matrix_t* result) {
  if (a->width != b->height)
    return -1;
  
  result->width = b->width;
  result->height = a->height;
  
  result->content = malloc(sizeof(int*) * result->height);
  for (int i = 0; i < result->height; i++)
    result->content[i] = malloc(sizeof(int) * result->width);

  for (int i = 0; i < result->height; i++)
    for (int j = 0; j < result->width; j++)
      result->content[i][j] = mul_vectors(a, b, i, j);

  return 0;
}

void print_matrix(matrix_t* a) {
  for (int i = 0; i < a->height; i++) {
    for (int j = 0; j < a->width; j++) 
      printf("%d ", a->content[i][j]);
    printf("\n");
  }
  printf("\n");
}