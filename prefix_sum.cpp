#include <iostream>
#include <vector>
#include "prefix_sum.h"
#include <omp.h>
using namespace std;

/*
void parallel_prefix_sum(vector<int>& A){
  for (unsigned int i = 0; i < ceil(log2(A.size())); i++){
    vector<int> B = A;
    #pragma omp parallel for
    for (unsigned int j = 0; j < A.size(); j++){
      if (j >= pow(2,i)){
        A[j] += B[j-pow(2,i)];
      }
    }
  }
  return;
} */

void parallel_prefix_sum(vector<int>& A){
  for (unsigned int i = 1; i < A.size();  i++){
    A[i] += A[i-1];
  }
  return;
}
