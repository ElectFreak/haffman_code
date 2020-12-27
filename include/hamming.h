#pragma once

typedef int block_t[4];
typedef int code_word_t[7];
typedef int control_sum_t[3];

void get_code(int* block, int* code_word);
void get_control_sum(int* code_word, int* control_sum);
int get_err(int* control_sum);
void reverse_random_bit(int* bit_seq, int size);
int* msg_to_bits(char* msg);
int* bits_to_code_words(int* bits, int size);
void bits_to_msg(int* bits, char* msg, int len);
int* code_words_to_bits(int* code_blocks, int size);
void decode(int* code_word, int* block);
void fix_bit_in_code_words(int* code_words, int size);