#pragma once
#include <vector>
#include <math.h>
using namespace std;

/*static void parallel_prefix_sum(vector<int>& A){
  for (unsigned int i = 1; i < A.size();  i++){
    A[i] += A[i-1];
  }
  return;
}*/

void parallel_prefix_sum(vector<int>& A);
