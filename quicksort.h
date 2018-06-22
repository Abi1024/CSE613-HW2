#pragma once
#include <vector>
#include "random.h"
#include "prefix_sum.h"

void print_vector(const std::vector<unsigned long long>&);
void print_vector(const std::vector<int>& A);
void print_vector(const std::vector<double>& A);
void print_vector(const std::vector<unsigned int>& A);
std::vector<int> parallel_partition(std::vector<double>&,int,int,double, bool verbose = false);
void parallel_randomized_quicksort(std::vector<double>& A, int q, int r, int m, int thread_ID, bool verbose = false, int depth = 0);
