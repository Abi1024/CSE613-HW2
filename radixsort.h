#pragma once
#include <vector>
#include <math.h>
#include "prefix_sum.h"
using namespace std;

void print2d_vector(vector<vector<long>>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    for (unsigned int j = 0; j < A[0].size(); j++){
      cout  << A[i][j] << " ";
    }
    cout << ",";
  }
  cout << endl;
}

void par_counting_rank(const vector<unsigned long long> & S, int n, int d, vector<unsigned int>& r, int p){
  //cout << "inside par counting rank, n: " << n << " d: " << d << " p: " << p << endl;
  vector<vector<int>> f((1 << d),vector<int>(p,0));
  vector<vector<int>> r1((1 << d),vector<int>(p,0));
  //cout << "f: " << endl;
  //print2d_vector(f);
  vector<int> js(p,0);
  vector<int> je(p,0);
  vector<int> ofs(p,0);
  //cout << "S: " << endl;
  //print_vector(S);
  //print_vector(r);
  //cout << "first parallel loop" << endl;
  #pragma omp parallel for //THIS IS A GOOD LOOP, KEEP IT!!!!!
  for (int i = 0; i < p; i++){
    //cout << "currently on processor: " << i << endl;
    js[i] = i*floor((float)n/p) ;
    je[i] = (i+1 < p) ? ((i+1)*floor((float)n/p)) : n;
    //cout << "i: " << i << " js[i]: " << js[i] << endl;
    //cout << "i: " << i << " je[i]: " << je[i] << endl;
    for (int j = js[i]; j < je[i]; j++){
      f[S[j]][i]++;
    }
  }
  //cout << "f: (After processor counts)" << endl;
  //print2d_vector(f);
  for (int j = 0; j < (1 << d); j++){
    parallel_prefix_sum(f[j]);
  }
  //cout << "f: (After prefix sum)" << endl;
  //print2d_vector(f);
  //cout << "second parallel loop" << endl;
  #pragma omp parallel for //this loop is fine
  for (int i = 0; i < p; i++){
    ofs[i] = 1;
    for (int j = 0; j < (1 << d); j++){
      //cout << "j: " << j << "  ofs[i]: " << ofs[i] << endl;
      r1[j][i] = (i == 0) ? ofs[i]: (ofs[i] + f[j][i-1]);
      ofs[i] += f[j][p-1];
    }
    //cout << "r1: " << endl;
    //print2d_vector(r1);
    for (int j = js[i]; j < je[i]; j++){
      r[j] = r1[S[j]][i];
      r1[S[j]][i]++;
    }
  }
}
unsigned long extract_bit_segment(unsigned long long A, int start, int end){
  return  (A << (64-end)) >> (64-end+start);
}

void parallel_radix_sort(vector<unsigned long long >& A, int n, int b, int p){
  //cout << "inside function radix_sort" << endl;
  vector<unsigned long long> S(n);
  vector<unsigned int> r(n);
  vector<unsigned long long> B(n);
  //cout << "WTF: " << n/p*log(n) << endl;
  int d = max(ceil(log2((double)n/(p*log2(n)))),1.0);
  //cout << "d : " << d << endl;
  for (int k = 0; k < b; k += d){
    //cout << "currently on bit: " << k << endl;
    int q = (k+d <= b) ? d : (b-k);
    //cout << "q: " << q << endl;
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
      S[i] = extract_bit_segment(A[i],k,k+q);
    }
    //cout << "Last 2 bits: ";
    //print_vector(S);
    //cout << "about to do par counting rank" << endl;
    par_counting_rank(S,n,q,r,p);
    //cout << "done with par counting rank" << endl;
    //cout << "Ranks: ";
    //print_vector(r);
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
      B[r[i]-1] = A[i];
    }
    //cout << "done with first update" << endl;
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
      A[i] = B[i];
    }
    //cout << "done with second update" << endl;
  }
  return;
}
