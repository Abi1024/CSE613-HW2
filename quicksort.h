#pragma once
#include <vector>
#include "random.h"

void print_vector(const std::vector<unsigned long long>&);
void print_vector(const std::vector<int>& A);
void print_vector(const std::vector<float>& A);
void print_vector(const std::vector<unsigned int>& A);
int parallel_partition(std::vector<float>&,int,int,float);
void parallel_randomized_quicksort(std::vector<float>& A, int q, int r, int m, int thread_ID);
