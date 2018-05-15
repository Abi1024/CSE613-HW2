#pragma once
#include <vector>
#include "random.h"

void print_vector(const std::vector<long>&);
void print_vector(const std::vector<int>& A);
void print_vector(const std::vector<float>& A);
int parallel_partition(std::vector<float>&,int,int,float);
void parallel_randomized_quicksort(std::vector<float>& A, int q, int r, int thread_ID);
