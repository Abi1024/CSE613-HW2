#pragma once
#include <vector>

void check_sorted(vector<unsigned long long>& A){
  for (unsigned int i = 0; i < A.size()-1; i++){
    if (A[i] > A[i+1]){
      cout << "ERROR! NOT SORTED!" << endl;
      exit(1);
    }
  }
}

void check_sorted(vector<double>& A){
  for (unsigned int i = 0; i < A.size()-1; i++){
    if (A[i] > A[i+1]){
      cout << "ERROR! NOT SORTED!" << endl;
      exit(1);
    }
  }
}
