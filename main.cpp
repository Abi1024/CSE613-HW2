#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include <fstream>
#include "mst.h"
#include "quicksort.h"
#include "radixsort.h"
#include "check_sorted.h"
#include "error.h"
#include <iomanip>
#include <string>
using namespace std;
int* state;
ofstream error[50];


void task1B_1(){
  ofstream out;
  out.open("task1B_1.csv");
  out << "n, Time (ms) " << endl;
  bool flag = true;
  int m = 32;
  int n = 128;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      vector<double> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          cout << "number of actual threads: " << omp_get_num_threads() << endl;
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num(),false);
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    out << n << "," << total_time*1000 << endl;
    if (total_time > 15){
      flag = false;
    }
    n *= 2;
  }
  out.close();
}

void task1B_2(){
  ofstream out;
  out.open("task1B_2.csv");
  out << "m, Time (ms) " << endl;
  bool flag = true;
  int m = 32;
  int n = 67108864;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      std::vector<double> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num(),false);
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "m: " << m << "\t Time(ms): " << total_time*1000 << endl;
    out << m << "," << total_time*1000 << endl;
    if (total_time > 60){
      flag = false;
    }
    m *= 2;
  }
  out.close();
}

void task1C_1(){
  ofstream out;
  out.open("task1C_1.csv");
  out << "n, Time (ms) " << endl;
  bool flag = true;
  int m = 64;
  int n = 1024;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      vector<double> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num(),false);
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    out << n << "," << total_time*1000 << endl;
    if (total_time > 120){
      flag = false;
    }
    n *= 2;
  }
  out.close();
}

void task1C_2(){
  ofstream out;
  out.open("task1C_2.csv");
  out << "n, Time (ms) " << endl;
  bool flag = true;
  int n = 1024;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      vector<unsigned long long> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_radix_sort(A,A.size(),64,omp_get_num_threads());
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    out << n << "," << total_time*1000 << endl;
    if (total_time > 120){
      flag = false;
    }
    n *= 2;
  }
  out.close();
}

void task1C_3(){
  ofstream out;
  out.open("task1C_3.csv");
  out << "Number of cores, Time (ms) " << endl;
  bool flag = true;
  int m = 64;
  //int n = 134217728;
  int n = 268435456;
  int num_cores = 1;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    omp_set_num_threads(num_cores);
    for (int j = 0; j < num_runs; j++){
      vector<double> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%100000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num(),false);
        }
      }
      double time = omp_get_wtime() - start_time;
      check_sorted(A);
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "Number of cores: " << num_cores << "\t Time(ms): " << total_time*1000 << endl;
    out << num_cores << "," << total_time*1000 << endl;
    if ((total_time > 120)||(num_cores > omp_get_num_procs())){
      flag = false;
    }
    num_cores++;
  }
  out.close();
}

void task1C_4(){
  ofstream out;
  out.open("task1C_4.csv");
  out << "Number of cores, Time (ms) " << endl;
  bool flag = true;
  int n = 134217728;
  //int n = 268435456;
  int num_cores = 1;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    omp_set_num_threads(num_cores);
    for (int j = 0; j < num_runs; j++){
      vector<unsigned long long> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          parallel_radix_sort(A,A.size(),64,omp_get_num_threads());
        }
      }
      double time = omp_get_wtime() - start_time;
      check_sorted(A);
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "Number of cores: " << num_cores << "\t Time(ms): " << total_time*1000 << endl;
    out << num_cores << "," << total_time*1000 << endl;
    if ((total_time > 120)||(num_cores > omp_get_num_procs())){
      flag = false;
    }
    num_cores++;
  }
  out.close();
}

void task1D_1(){
  ofstream out;
  out.open("task1D_1.csv");
  out << "n, Time (ms) " << endl;
  bool flag = true;
  int m = 64;
  int n = 64;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      vector<double> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          //cout << "number of actual threads: " << omp_get_num_threads() << endl;
          parallel_randomized_quicksort(A,0,A.size()-1,m,omp_get_thread_num(),false);
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    out << n << "," << total_time*1000 << endl;
    if (n >= 268435456){
      flag = false;
    }
    n *= 2;
  }
  out.close();
}

void task1D_2(){
  ofstream out;
  out.open("task1D_2.csv");
  cout << "setting up output" << endl;
  out << "n, Time (ms) " << endl;
  bool flag = true;
  int n = 64;
  int num_runs = 1;
  while(flag){
    double total_time = 0;
    for (int j = 0; j < num_runs; j++){
      vector<unsigned long long> A(n);
      for (unsigned int i = 0; i < A.size(); i++){
        A[i] = rand(0)%1000000;
      }
      cout << "ITERATION" << endl;
      double start_time = omp_get_wtime();
      #pragma omp parallel
      {
        #pragma omp single
        {
          cout << "number of actual threads: " << omp_get_num_threads() << endl;
          parallel_radix_sort(A,A.size(),64,omp_get_num_threads());
        }
      }
      double time = omp_get_wtime() - start_time;
      //print_vector(A);
      total_time += time;
    }
    total_time /= num_runs;
    cout << "n: " << n << "\t Time(ms): " << total_time*1000 << endl;
    out << n << "," << total_time*1000 << endl;
    if (n >= 268435456){
      flag = false;
    }
    n *= 2;
  }
  out.close();
}

void task2B_1(string filename){
  string file = filename.substr(0,filename.length()-7)+"-out.txt";
  ifstream in;
  in.open(filename.c_str());
  int num_vertices;
  in >> num_vertices;
  int num_edges;
  in >> num_edges;
  vector<Edge> E(num_edges);
  cout << "num_vertices: " << num_vertices << endl;
  cout << "edges: " << num_edges << endl;
  for (int i = 0; i < num_edges; i++){
    int vertex1,vertex2;
    double edge;
    in >> vertex1 >> vertex2 >> edge;
    E[i] = (Edge(vertex1,vertex2,edge));
  }
  in.close();
  unsigned int size = E.size();
  for (unsigned int i = 0; i < size; i++){
    E.push_back(Edge(E[i].v,E[i].u,E[i].weight));
  }
  cout << "read the inputs" << endl;
  vector<int> MST(E.size(),0);
  double start_time = omp_get_wtime();
  par_randomized_mst_priority_cw(num_vertices,E,MST,true);
  double time = omp_get_wtime() - start_time;
  cout << "Time(ms): " << time*1000 << endl;
  cout << "printing MST" << endl;
  double cost = 0;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
    }
  }
  ofstream out;
  out.open(file.c_str());
  out << setprecision(3) <<  fixed << cost << endl;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
      out << setprecision(3) << fixed << E[i].u << " " << E[i].v << " "  << E[i].weight << endl;
    }
  }
  out.close();
}

void task2B_2(string filename){
  string file = filename.substr(0,filename.length()-7)+"-out.txt";
  ifstream in;
  in.open(filename.c_str());
  int num_vertices;
  in >> num_vertices;
  int num_edges;
  in >> num_edges;
  vector<Edge> E(num_edges);
  cout << "num_vertices: " << num_vertices << endl;
  cout << "edges: " << num_edges << endl;
  for (int i = 0; i < num_edges; i++){
    int vertex1,vertex2;
    double edge;
    in >> vertex1 >> vertex2 >> edge;
    E[i] = (Edge(vertex1,vertex2,edge));
  }
  in.close();
  unsigned int size = E.size();
  for (unsigned int i = 0; i < size; i++){
    E.push_back(Edge(E[i].v,E[i].u,E[i].weight));
  }
  cout << "read the inputs" << endl;
  vector<int> MST(E.size(),0);
  double start_time = omp_get_wtime();
  par_randomized_mst_priority_cw(num_vertices,E,MST,false);
  double time = omp_get_wtime() - start_time;
  cout << "Time(ms): " << time*1000 << endl;
  cout << "printing MST" << endl;
  double cost = 0;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
    }
  }
  ofstream out;
  out.open(file.c_str());
  out << setprecision(3) <<  fixed << cost << endl;
  for (unsigned int i = 0; i < MST.size(); i++){
    if (MST[i] == 1){
      cost += E[i].weight;
      out << setprecision(3) << fixed << E[i].u << " " << E[i].v << " "  << E[i].weight << endl;
    }
  }
  out.close();
  cout << "Done" << endl;
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
  vector<double> A(800000);
  for (unsigned int i = 0; i < A.size(); i++){
    A[i] = rand(0)%10000;
  }
  //\\vector<long> A = {1,10,10,6,8,14,20,10};
  //print_vector(A);
  double start_time = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp single
    {
      cout << omp_get_num_threads() << endl;
      parallel_randomized_quicksort(A,0,A.size()-1,64,0);
    }
  }
  double time = omp_get_wtime() - start_time;
  //print_vector(A);
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
}

void test_parallel_partition(){
  vector<double> A(100);
  for (unsigned int i = 0; i < A.size(); i++){
    //A[i] = rand(0)%20;
    /*if (rand(0)%2 == 0){
      A[i] = 5;
    }else{
      A[i] = rand(0)%20;
    }*/
    A[i] = rand(0)%20;
  }
  //vector<double> A = {1,10,10,6,8,14,20,10};
  print_vector(A);
  int random_index = rand(0) % A.size();
  double random_number = A[random_index];
  //int random_number = 5;
  double start_time = omp_get_wtime();
  vector<int> result = parallel_partition(A,0,A.size()-1,random_number);
  double time = omp_get_wtime() - start_time;
  print_vector(A);
  cout << result[0] << " " << result[1] << " " << random_number << endl;
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
  E.push_back(Edge(1,2,5));
  E.push_back(Edge(1,3,2));
  E.push_back(Edge(2,3,2));
  E.push_back(Edge(2,4,3));
  E.push_back(Edge(2,5,7));

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
}

void create_edges2(vector<Edge>& E){
  E.push_back(Edge(1,2,100));
  E.push_back(Edge(1,3,1));
  E.push_back(Edge(3,4,2));
  E.push_back(Edge(3,5,3));
  E.push_back(Edge(5,6,200));
  E.push_back(Edge(2,4,4));
  E.push_back(Edge(4,6,5));
  E.push_back(Edge(1,2,100));
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
  int num_vertices = 6;
  vector<Edge> E;
  create_edges2(E);
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


int main(int argc, const char* argv[]){
  cout << "running main" << endl;
  cout << "number of available cores: " << omp_get_num_procs() << endl;
  init_rand_state(24);
  omp_set_num_threads(omp_get_num_procs());
  //omp_set_num_threads(24);
  omp_set_nested(1);
  omp_set_max_active_levels(6);
  for (int i = 0; i < 50; i++){
    error[i].open("err" + to_string(i) + ".txt");
  }
  string task = argv[1];
  cout << task << endl;
  if (task == "task1B_1" ){
    task1B_1();
  }else if (task == "task1B_2" ){
    task1B_2();
  }else if (task == "task1C_1" ){
    task1C_1();
  }else if (task == "task1C_2" ){
    task1C_2();
  }else if (task == "task1C_3" ){
    task1C_3();
  }else if (task == "task1C_4" ){
    task1C_4();
  }else if (task == "task1D_1" ){
    task1D_1();
  }else if (task == "task1D_2" ){
    task1D_2();
  }else if (task == "task2B_1" ){
    string filename = argv[2];
    task2B_1(filename);
  }else if (task == "task2B_2" ){
    string filename = argv[2];
    task2B_2(filename);
  }
  //test_prefix_sum();
  //test_parallel_partition();.
  //test_parallel_randomized_quicksort();
  //test_mst_radix();
  //test_par_simulate_priority_cw_using_radix_sort();
  for (int i = 0; i < 50; i++){
    error[i].close();
  }
  delete_state();
  return 0;
}
