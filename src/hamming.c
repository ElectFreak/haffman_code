#include <stdio.h> // remove
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "hamming.h"

const int H[3][7] = {
  { 0, 0, 0, 1, 1, 1, 1 },
  { 0, 1, 1, 0, 0, 1, 1 },
  { 1, 0, 1, 0, 1, 0, 1 }
};

const int G[7][4] = {
  { 1, 0, 1, 1 },
  { 1, 1, 0, 1 },
  { 0, 0, 0, 1 }, // *
  { 1, 1, 1, 0 },
  { 0, 0, 1, 0 }, // *
  { 0, 1, 0, 0 }, // *
  { 1, 0, 0, 0 }  // *
};

void get_code(int* block, int* code_word) {
  for (int i = 0; i < 7; i++) {
    int sum = 0;
    for (int j = 0; j < 4; j++) {
      sum += block[j] * G[i][j];
    }
    code_word[i] = sum % 2;
  }
}

void decode(int* code_word, int* block) {
  block[0] = code_word[6];
  block[1] = code_word[5];
  block[2] = code_word[4];
  block[3] = code_word[2];
}

void get_control_sum(int* code_word, int* control_sum) {
  for (int i = 0; i < 3; i++) {
    int sum = 0;
    for (int j = 0; j < 7; j++) {
      sum += H[i][j] * code_word[j];
    }
    control_sum[i] = sum % 2;
  }
}

int get_err(int* control_sum) {
  for (int i = 0; i < 7; i++) {
    int is_equal = 1;
    
    for (int j = 0; j < 3; j++) 
      if (control_sum[j] != H[j][i])
        is_equal = 0;
    
    if (is_equal)
      return i;
  }

  return -1;
}

int* msg_to_bits(char* msg) {
  int len = strlen(msg);
  int* bits = malloc(sizeof(int) * len * 8);

  for (int i = 0; i < len; i++) 
    for (int j = 0; j < 8; j++) 
      bits[i * 8 + j] = ((msg[i] >> j) & 1);

  return bits; 
}

void bits_to_msg(int* bits, char* msg, int len) {
  for (int i = 0; i < len; i ++) {
    msg[i] = 0;
    
    for (int j = 0; j < 8; j++)
      msg[i] |= bits[i * 8 + j] << j;
  }
  
  msg[len] = 0;
}

void reverse_random_bit(int* bit_seq, int size) {
  srand(time(0)); 
  int pos = rand() % size;
  bit_seq[pos] = 1 - bit_seq[pos];
}

int* blocks_to_code_words(int* bits, int size) { 
  if ((size % 4) != 0) {
    printf("error\n");
  }
  int* code_words = malloc(sizeof(int) * (size / 4) * 7);
  for (int i = 0; i < size / 4; i++) {
    get_code(bits + i * 4, code_words + i * 7);
  }

  return code_words;
}

int* code_words_to_bits(int* code_blocks, int size) {
  int* bits = malloc(sizeof(int) * (size / 7) * 4);
  for (int i = 0; i < size / 7; i++) {
    decode(code_blocks + i * 7, bits + i * 4);
  }

  return bits;
}

void fix_bit_in_code_words(int* code_words, int size) {
  for (int i = 0; i < size; i += 7) {
    control_sum_t control_sum;
    get_control_sum(code_words + i, control_sum);
    int err = get_err(control_sum);
    if (err != -1) {
      code_words[i + err] = 1 - code_words[i + err];
    }
  }
}