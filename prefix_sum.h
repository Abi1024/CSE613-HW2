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

static void parallel_prefix_sum(vector<int>& A){
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
}
