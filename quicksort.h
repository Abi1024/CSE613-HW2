#pragma once
#include <vector>
#include "random.h"

void print_vector(std::vector<int>&);
int parallel_partition(std::vector<int>&,int,int,int);
void parallel_randomized_quicksort(std::vector<int>& A, int q, int r, int thread_ID);
