#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include <fstream>
#include "mst.h"
#include "quicksort.h"
#include "radixsort.h"
using namespace std;
int* state;

void task1B(){
  ofstream output;
  bool flag = true;
  int m = 32;
  int n = 64;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < 1; j++){
      vector<float> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num());
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= 1;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    if (total_time > 15){
      flag = false;
    }
    n *= 2;
  }
}

void test_prefix_sum(){
  vector<int> A(2000000);
  for (unsigned int i = 0; i < A.size(); i++){
    A[i] = rand(0)%10000000;
  }
  //print_vector(A);
  double start_time = omp_get_wtime();
  parallel_prefix_sum(A);
  double time = omp_get_wtime() - start_time;
  //print_vector(A);
	cout << "\t Time(ms): " << time*1000 << endl;
}

void test_parallel_randomized_quicksort(){
  vector<float> A(32000);
  for (unsigned int i = 0; i < A.size(); i++){
    A[i] = rand(0)%100000;
  }
  //vector<long> A = {1,10,10,6,8,14,20,10};
  //print_vector(A);
  double start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      //cout << omp_get_num_threads() << endl;
      parallel_randomized_quicksort(A,0,A.size()-1,32,omp_get_thread_num());
    }
  }
  double time = omp_get_wtime() - start_time;
  //print_vector(A);
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
}

void test_radix_sort(){
  vector<unsigned long long> A;
  map<long,bool> record;
  for (int i = 0; i < 100; i++){
    unsigned long long random_number = rand(0)%10000;
    if (record.find(random_number) == record.end()){
      A.push_back(random_number);
      record[random_number] = true;
    }else{
      i--;
    }
  }
  //vector<long> A = {1,10,10,6,8,14,20,10};
  print_vector(A);
  vector<long> r = vector<long>(A.size(),0);
  double start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      //cout << omp_get_num_threads() << endl;
      parallel_radix_sort(A,A.size(),32,omp_get_num_threads());
    }
  }
  double time = omp_get_wtime() - start_time;
  print_vector(A);
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
}

void print_edges(const vector<Edge>& E){
  for (unsigned int i = 0; i < E.size(); i++){
    cout << E[i].u << " " << E[i].v << " " << E[i].weight << endl;
  }
}

/*
void create_edges(vector<Edge>& E){
  E.push_back(Edge(1,2,5));
  E.push_back(Edge(1,3,2));
  E.push_back(Edge(2,5,7));
  E.push_back(Edge(2,4,3));
  E.push_back(Edge(2,3,2));
  E.push_back(Edge(3,4,3));
  E.push_back(Edge(3,7,9));
  E.push_back(Edge(4,5,2));
  E.push_back(Edge(4,7,6));
  E.push_back(Edge(5,6,8));
  E.push_back(Edge(5,7,5));
  E.push_back(Edge(5,8,7));
  E.push_back(Edge(6,8,3));
  E.push_back(Edge(6,9,4));
  E.push_back(Edge(7,8,2));
  unsigned int size = E.size();
  for (unsigned int i = 0; i < size; i++){
    E.push_back(Edge(E[i].v,E[i].u,E[i].weight));
  }
}*/

void create_edges(vector<Edge>& E){
  E.push_back(Edge(2,3,5));
  E.push_back(Edge(2,5,9));
  E.push_back(Edge(2,6,1));
  E.push_back(Edge(3,4,3));
  E.push_back(Edge(3,5,1));
  E.push_back(Edge(3,6,2));
  E.push_back(Edge(4,5,14));
  E.push_back(Edge(4,6,7));

  unsigned int size = E.size();
  for (unsigned int i = 0; i < size; i++){
    E.push_back(Edge(E[i].v,E[i].u,E[i].weight));
  }
}

void test_par_simulate_priority_cw_using_radix_sort(){
  int num_vertices = 9;
  vector<Edge> E;
  create_edges(E);
  vector<int> R(num_vertices);
  par_simulate_priority_cw_using_radix_sort(R.size(), E, R);
  print_vector(R);
}

void test_par_simulate_priority_cw_using_binary_search(){
  int num_vertices = 9;
  vector<Edge> E;
  create_edges(E);
  vector<int> R(num_vertices);
  par_simulate_priority_cw_using_binary_search(R.size(), E, R);
  print_vector(R);
}

void test_mst_radix(){
  int num_vertices = 9;
  vector<Edge> E;
  create_edges(E);
  vector<int> MST(E.size(),0);
  par_randomized_mst_priority_cw(num_vertices,E,MST,true);
  cout << "printing MST" << endl;
  int cost = 0;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
      cout << "i: " << i << " u: " << E[i].u << " v " << E[i].v << " weight: " << E[i].weight << endl;
    }
  }
  cout << "cost: " << cost <<  endl;
}

void test_mst_binary_search(){
  int num_vertices = 9;
  vector<Edge> E;
  create_edges(E);
  vector<int> MST(E.size(),0);
  par_randomized_mst_priority_cw(num_vertices,E,MST,false);
  cout << "printing MST" << endl;
  int cost = 0;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
      cout << "i: " << i << " u: " << E[i].u << " v " << E[i].v << " weight: " << E[i].weight << endl;
    }
  }
  cout << "cost: " << cost <<  endl;
}

/*void test_XXX(){
  vector<float> A(64);
  for (unsigned int i = 0; i < A.size(); i++){
    A[i] = rand(0)%1000;
  }
  //vector<long> A = {1,10,10,6,8,14,20,10};
  print_vector(A);
  double start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      //cout << omp_get_num_threads() << endl;
      parallel_randomized_quicksort(A,1,7,32,omp_get_thread_num());
    }
  }
  double time = omp_get_wtime() - start_time;
  print_vector(A);
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
}*/


int main(){
  init_rand_state(1);
  omp_set_num_threads(1);
  //omp_set_dynamic(true);
  //omp_set_num_threads(omp_get_num_procs());
  //omp_set_nested(1);
  //task1B();
  test_prefix_sum();
  return 0;
}
