#pragma once
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <math.h>
#include "quicksort.h"
#include "radixsort.h"
#include "check_sorted.h"
using namespace std;

class Edge{
  public:
    int u;
    int v;
    double weight;
    Edge(int u, int v, double weight): u(u), v(v), weight(weight){};
    Edge(): u(0), v(0), weight(0){};
};

void par_simulate_priority_cw_using_radix_sort(int n,vector<Edge>&  E, vector<int>& R){
  //cout << "inside par_simulate_radix_sort" << endl;
  vector<unsigned long long> A(E.size());
  int k = ceil(log2(E.size()))+1;
  //cout << k << endl;
  cout << "k: " << k << endl;
  //#pragma omp parallel for
  //encode the edge's weight and first vertex into A[i].
  for (unsigned int i = 0; i < E.size(); i++){
    //cout << "i: " << i << " source: " << E[i].u  << endl;
    if (E[i].u != E[i].v){
      A[i] = ((unsigned long long)(E[i].u-1) << k) + i ;
    }else{
      A[i] = ((unsigned long long)(E[i].u-1) << k) + E.size() ;
    }
    //cout << "A[i]: " << A[i] << endl;
    //cout << "i: " << i << " u: " << (A[i] >> k) << " j: " << A[i] - ((A[i] >> k) << k) << endl;
  }
  //cout << "Done with setting up augmented edges." << endl;
  //print_vector(A);
  parallel_radix_sort(A,E.size(),k+ceil(log2(n)),omp_get_num_threads());
  //#pragma omp parallel for
  for (unsigned int i = 0; i < E.size(); i++){
    unsigned long long u = (A[i] >> k);
    unsigned int j = A[i] - (u << k);
    //cout << "i: " << i << " u: " << u << " j: " << j << endl;
    if ((i == 0) || (u != (A[i-1] >> k))){
      R[u] = j;
    }
  }
}

void par_simulate_priority_cw_using_binary_search(int n,vector<Edge>&  E, vector<int>& R){
  cout << "inside par_simulate_binary_search" << endl;
  vector<unsigned int> B(n);
  vector<unsigned int> l(n,0);
  vector<unsigned int> h(n,E.size()-1);
  vector<unsigned int> lo(n);
  vector<unsigned int> hi(n);
  vector<unsigned int> md(n);
  int iterations = 1 + ceil(log2(E.size()));
  for (int k = 1; k < iterations; k++){
    //cout << "k: " << k << endl;
    B = vector<unsigned int>(n,0);
    lo = l;
    hi = h;
    //cout << "lo:";
    //print_vector(lo);
    //cout << "hi: ";
    //print_vector(hi);
    //#pragma omp parallel for
    for (unsigned int i = 0; i < E.size(); i++){
      int u = E[i].u - 1;
      md[u] = floor((lo[u]+hi[u])/2.0);
      if ((i  >= lo[u]) && (i  <= md[u]) && (E[i].u != E[i].v)){
        B[u] = 1;
      }
    }
    //cout << "md:";
    //print_vector(md);
    //cout << "B:";
    //print_vector(B);
    //#pragma omp parallel for
    for (unsigned int i = 0; i < E.size(); i++){
      int u = E[i].u - 1;
      if ((B[u] == 1)){
        h[u] = md[u];
      }else if ((B[u] == 0) && (i  > md[u])&&(i <= hi[u])){
        l[u] = md[u] + 1;
      }
    }
    //cout << "l:";
    //print_vector(l);
    //cout << "h:";
    //print_vector(h);
  }
  //#pragma omp parallel for
  for (unsigned int i = 0; i < E.size(); i++){
    int u = E[i].u - 1;
    if (i  == l[u]){
      R[u] = i;
    }
  }
}

void par_randomized_mst_priority_cw(int n, vector<Edge>& Edges, vector<int>& MST, bool radix_sort){
  vector<long> L(n);
  vector<int> C(n);
  vector<int> R(n);
  //cout << "inside  par_randomized_mst_priority_cw" <<  endl;
  vector<double> weights(Edges.size());
  map<double,list<vector<int>>> record;
  for (unsigned int i = 0; i < Edges.size(); i++){
    weights[i] = Edges[i].weight;
    if ( record.find(weights[i]) == record.end() ) {
        record[weights[i]] = list<vector<int>>();
    }
    record[weights[i]].push_back({Edges[i].u,Edges[i].v});
  }

  //print_vector(weights);
  //cout << "sorting weights array " << endl;
  parallel_randomized_quicksort(weights,0,weights.size()-1,32,0);

  for (unsigned int i = 0; i < Edges.size(); i++){
    vector<int> temp = record[weights[i]].front();
    record[weights[i]].pop_front();
    Edges[i] = Edge(temp[0],temp[1],weights[i]);
  }
  //cout << "sorted the edges" << endl;
  /*for (unsigned int i = 0; i < Edges.size(); i++){
    cout << "i: " << i << " u: " << Edges[i].u << " v " << Edges[i].v << " weight: " << Edges[i].weight << endl;
  }*/

  vector<Edge> E = Edges;
  //#pragma omp parallel for
  for (int i = 0; i < n; i++){
    L[i] = i;
  }
  bool F = (E.size() > 0) ? true : false;
  int stop = 0;
  while (F){
    //cout << "Iteration==================================== " << endl;
    stop++;
    cout << stop << endl;
    //#pragma omp parallel for
    for (int v = 0; v < n; v++){
      C[v] = rand(omp_get_thread_num())%2; //0 is Tails, 1 is heads
    }
    //cout << "coin tosses" << endl;
    //print_vector(C);
    //cout << "running par_simulate"  << endl;
    if (radix_sort){
      par_simulate_priority_cw_using_radix_sort(n,E,R);
    }else{
      par_simulate_priority_cw_using_binary_search(n,E,R);
    }
    //print_vector(R);
    //cout << "examining edges from shortest" << endl;

    //#pragma omp parallel for
    for (unsigned int i = 0; i < E.size(); i++){
      long u = E[i].u;
      long v = E[i].v;
      //cout << "i: " << i << " coin toss matches: " << (((C[u-1] == 0)&&(C[v-1] == 1)) ? 1 : 0) << endl;
      if ((C[u-1] == 0)&&(C[v-1] == 1)&&(R[u-1] == (int) (i))){
        //cout << "coin toss valid and index valid " << endl;
        L[u-1] = v-1;
        MST[i] = 1;
      }
    }
    //#pragma omp parallel for
    for (unsigned int i = 0; i < E.size(); i++){
      E[i] = Edge(L[E[i].u-1]+1,L[E[i].v-1]+1,E[i].weight);
    }
    //cout << "updated edge list after some pruning" << endl;
    /*
    for (unsigned int i = 0; i < E.size(); i++){
      cout << "i: " << i << " u: " << E[i].u << " v " << E[i].v << " weight: " << E[i].weight << endl;
    }*/

    F = false;
    //#pragma omp parallel for
    for (unsigned int i = 0; i < E.size(); i++){
      if (E[i].u != E[i].v){
        F = true;
      }
    }
  }
}
