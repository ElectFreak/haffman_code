#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hamming.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    return -1;
  }

  char* msg = argv[1];
  int len = strlen(msg);
  int* bits = msg_to_bits(msg);
  
  char* decode_msg = malloc(sizeof(char) * len + 1);
  int* code_words = blocks_to_code_words(bits, len * 8);
  
  // reverse_random_bit(code_words, len * 2 * 7);
  code_words[2] = 1 - code_words[2]; // reverse "random" bit
  int* broken_bits = code_words_to_bits(code_words, len * 2 * 7);
  bits_to_msg(broken_bits, decode_msg, len);
  printf("Break single bit in message: %s\n", decode_msg);

  fix_bit_in_code_words(code_words, len * 2 * 7);
  int* fixed_bits = code_words_to_bits(code_words, len * 2 * 7);
  bits_to_msg(fixed_bits, decode_msg, len);
  printf("Fixed message: %s\n", decode_msg);

  free(bits);
  free(broken_bits);
  free(code_words);
  free(fixed_bits);
  free(decode_msg);
 
  return 0;
}