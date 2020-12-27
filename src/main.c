#include <stdio.h>
#include <stdlib.h>

#include "hamming.h"

int main(void) {
  char msg[] = "hello, world";
  int* bits = msg_to_bits(msg);
  char decode_msg[13];
  int* code_words = blocks_to_code_words(bits, 12 * 8);
  
  // reverse_random_bit(code_words, 13 * 4 * 7);
  code_words[2] = 1 - code_words[2]; // reverse "random" bit
  int* broken_bits = code_words_to_bits(code_words, 12 * 2 * 7);
  bits_to_msg(broken_bits, decode_msg, 12);
  printf("Break single bit in message: %s\n", decode_msg);

  fix_bit_in_code_words(code_words, 12 * 2 * 7);
  int* fixed_bits = code_words_to_bits(code_words, 12 * 2 * 7);
  bits_to_msg(fixed_bits, decode_msg, 12);
  printf("Fixed message: %s\n", decode_msg);

  free(bits);
  free(broken_bits);
  free(code_words);
  free(fixed_bits);
 
  return 0;
}