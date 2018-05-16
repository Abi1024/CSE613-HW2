#pragma once
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <math.h>
#include "quicksort.h"
#include "radixsort.h"
using namespace std;

class Edge{
  public:
    int u;
    int v;
    float weight;
    Edge(int u, int v, float weight): u(u), v(v), weight(weight){};
};

void par_simulate_priority_cw_using_radix_sort(int n,vector<Edge>&  E, vector<int>& R){
  cout << "inside par_simulate" << endl;
  vector<long> A(E.size());
  int k = ceil(log2(E.size()))+1;
  cout << "k: " << k << endl;
  for (unsigned int i = 0; i < E.size(); i++){
    if (E[i].u != E[i].v){
      A[i] = ((E[i].u-1) << k) + i ;
    }else{
      A[i] = ((E[i].u-1) << k) + E.size() ;
    }
  }
  //print_vector(A);
  parallel_radix_sort(A,E.size(),k+ceil(log2(n)),omp_get_num_threads());
  //print_vector(A);
  for (unsigned int i = 0; i < E.size(); i++){
    int u = (A[i] >> k);
    int j = A[i] - (u << k);
    //cout << "i: " << i << " u: " << u << " j: " << j << endl;
    if ((i == 0) || (u != (A[i-1] >> k))){
      R[u] = j;
    }
  }
}

void par_randomized_mst_priority_cw(int n, vector<Edge>& E, vector<Edge>& MST){
  vector<long> L(n);
  vector<long> C(n);
  vector<int> R(n);
  cout << "inside  par_randomized_mst_priority_cw" <<  endl;
  vector<float> weights(E.size());
  map<float,list<vector<int>>> record;
  for (unsigned int i = 0; i < E.size(); i++){
    weights[i] = E[i].weight;
    if ( record.find(weights[i]) == record.end() ) {
        record[weights[i]] = list<vector<int>>();
    }
    record[weights[i]].push_back({E[i].u,E[i].v});
  }

  print_vector(weights);
  cout << "sorting weights array " << endl;
  parallel_randomized_quicksort(weights,0,weights.size()-1,0);
  print_vector(weights);

  for (unsigned int i = 0; i < E.size(); i++){
    vector<int> temp = record[weights[i]].front();
    record[weights[i]].pop_front();
    E[i] = Edge(temp[0],temp[1],weights[i]);
  }
  cout << "printing sorted edges" << endl;
  for (unsigned int i = 0; i < E.size(); i++){
    cout << "i: " << i << " u: " << E[i].u << " v " << E[i].v << " weight: " << E[i].weight << endl;
  }

  vector<Edge> temp = E;

  for (int i = 0; i < n; i++){
    L[i] = i;
  }
  bool F = (E.size() > 0) ? true : false;
  int stop = 0;
  while (F){
    cout << "Iteration==================================== " << endl;
    stop++;
    if (stop == 10){
      exit(1);
    }
    for (int v = 0; v < n; v++){
      C[v] = rand(0)%2; //0 is Tails, 1 is heads
    }
    cout << "coin tosses" << endl;
    print_vector(C);
    cout << "running par_simulate"  << endl;
    par_simulate_priority_cw_using_radix_sort(n,E,R);
    print_vector(R);
    cout << "examining edges from shortest" << endl;
    for (unsigned int i = 0; i < E.size(); i++){
      long u = E[i].u;
      long v = E[i].v;
      cout << "i: " << i << " coin toss matches: " << (((C[u-1] == 0)&&(C[v-1] == 1)) ? 1 : 0) << endl;
      if ((C[u-1] == 0)&&(C[v-1] == 1)&&(R[u-1] == (int) (i))){
        cout << "coin toss valid and index valid " << endl;
        L[u-1] = v-1;
        MST.push_back(Edge(temp[i].u,temp[i].v,temp[i].weight));
        MST.push_back(Edge(temp[i].v,temp[i].u,temp[i].weight));
      }
    }
    for (unsigned int i = 0; i < E.size(); i++){
      E[i] = Edge(L[E[i].u-1]+1,L[E[i].v-1]+1,E[i].weight);
    }
    cout << "updated edge list after some pruning" << endl;

    for (unsigned int i = 0; i < E.size(); i++){
      cout << "i: " << i << " u: " << E[i].u << " v " << E[i].v << " weight: " << E[i].weight << endl;
    }

    F = false;
    for (unsigned int i = 0; i < E.size(); i++){
      if (E[i].u != E[i].v){
        F = true;
      }
    }
  }
}
