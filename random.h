#pragma once
extern int* state;

void init_rand_state(int num_threads);
int xorshift128(int* state, int size);
int rand(int id);
