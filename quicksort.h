#pragma once
#include <vector>
#include "random.h"

void print_vector(const std::vector<long>&);
int parallel_partition(std::vector<long>&,int,int,long);
void parallel_randomized_quicksort(std::vector<long>& A, int q, int r, int thread_ID);
