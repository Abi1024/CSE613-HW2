#pragma once
#include <vector>
#include <list>
#include <map>
#include <pair>
#include <math.h>
#include "quicksort.h"
#include "radixsort.h"
using namespace std;

class Edge{
  public:
    long u;
    long v;
    float weight;
    Edge(long u, long v, float weight): u(u), v(v), weight(weight){};
};

void par_simulate_priority_cw_using_radix_sort(int n,vector<Edge>&  E, vector<int>& R){
  cout << "inside par_simulate" << endl;
  vector<long> A(E.size());
  int k = ceil(log2(E.size()))+1;

  vector<float> weights(E.size());
  map<float,list<pair<int>>> record;

  for (unsigned int i = 0; i < E.size(); i++){
    weights[i] = E[i].weight;
    if ( record.find(weights[i]) == m.end() ) {
        record[weights[i]] = list<pair<int>>();
    }
    m[weights[i]].push_back(make_pair(E[i].u,E[i].v));
  }

  parallel_randomized_quicksort(weights,0,weights.size()-1,0);

  for (unsigned int i = 0; i < )

  for (unsigned int i = 0; i < E.size(); i++){
    A[i] = ((E[i].u-1) << k) + i ;
  }
  //print_vector(A);
  parallel_radix_sort(A,E.size(),k+ceil(log2(n)),omp_get_num_threads());
  //print_vector(A);
  for (unsigned int i = 0; i < E.size(); i++){
    int u = (A[i] >> k);
    int j = A[i] - (u << k);
    if ((i == 0) || (u != (A[i-1] >> k))){
      R[u] = j;
    }
  }
}

void par_randomized_mst_priority_cw(int n, vector<Edge> E, vector<int> MST){
  vector<long> L(n);
  vector<long> C(n);
  vector<int> R(n);
  map<
  //parallel_randomized_quicksort(A,0,A.size()-1,1);
  for (int i = 0; i < n; i++){
    L[i] = i;
  }
  bool F = (E.size() > 0) ? true : false;
  while (F){
    for (int v = 0; v < n; v++){
      C[v] = rand(0)%2; //0 is Tails, 1 is heads
    }
    par_simulate_priority_cw_using_radix_sort(n,E,R);
    for (unsigned int i = 0; i < E.size(); i++){
      long u = E[i].u;
      long v = E[i].v;
      if ((C[u-1] == 0)&&(C[v-1] == 1)&&(R[u-1] == (int) i)){
        L[u-1] = v;
        MST[i] = 1;
      }
    }
    /*
    for (unsigned int i = 0; i < E.size(); i++){
      E[i] =
    }*/
  }
}
