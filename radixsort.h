#pragma once
#include <vector>
#include <math.h>
#include "prefix_sum.h"
using namespace std;

void print2d_vector(vector<vector<int>>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    for (unsigned int j = 0; j < A[0].size(); j++){
      cout  << A[i][j] << " ";
    }
  }
  cout << endl;
}

void par_counting_rank(vector<int> S, int n, int d, vector<int>& r, int p){
  cout << "inside par counting rank" << endl;
  vector<vector<int>> f(pow(2,d),vector<int>(p,0));
  vector<vector<int>> r1(pow(2,d),vector<int>(p,0));
  cout << "f: " << endl;
  print2d_vector(f);
  vector<int> js(p,0);
  vector<int> je(p,0);
  vector<int> ofs(p,0);
  cout << "S: " << endl;
  print_vector(S);
  print_vector(r);
  for (int i = 0; i < p; i++){
    js[i] = i*floor((float)n/p) ;
    je[i] = (i+1 < p) ? ((i+1)*floor((float)n/p)) : n;
    cout << "i: " << i << " js[i]: " << js[i] << endl;
    cout << "i: " << i << " je[i]: " << je[i] << endl;
    for (int j = js[i]; j < je[i]; j++){
      f[S[j]][i]++;
    }
  }
  cout << "f: (After processor counts)" << endl;
  print2d_vector(f);
  for (int j = 0; j < pow(2,d); j++){
    parallel_prefix_sum(f[j]);
  }
  print2d_vector(f);
  for (int i = 0; i < p; i++){
    ofs[i] = 1;
    for (int j = 0; j < pow(2,d); j++){
      r1[j][i] = (i == 0) ? ofs[i]: (ofs[i] + f[j][i]);
      ofs[i] = ofs[i] + f[j][p];
    }
    for (int j = js[i]; j < je[i]; j++){
      r[j] = r1[S[j]][i];
      r1[S[j]][i]++;
    }
  }
}
