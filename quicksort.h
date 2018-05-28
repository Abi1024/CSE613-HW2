#pragma once
#include <vector>
#include "random.h"
#include "prefix_sum.h"

void print_vector(const std::vector<unsigned long long>&);
void print_vector(const std::vector<int>& A);
void print_vector(const std::vector<float>& A);
void print_vector(const std::vector<unsigned int>& A);
std::vector<int> parallel_partition(std::vector<float>&,int,int,float, bool verbose = false);
void parallel_randomized_quicksort(std::vector<float>& A, int q, int r, int m, int thread_ID, bool verbose = false);
