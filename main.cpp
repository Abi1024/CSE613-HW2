#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include "quicksort.h"
#include "radixsort.h"
using namespace std;
int* state;

/*int main(){
  init_rand_state(1);
  omp_set_num_threads(4);
  vector<long> A;
  map<long,bool> record;
  for (int i = 0; i < 32; i++){
    long random_number = rand(0)%1000;
    if (record.find(random_number) == record.end()){
      A.push_back(random_number);
      record[random_number] = true;
    }else{
      i--;
    }
  }
  print_vector(A);
  double start_time = omp_get_wtime();
  parallel_randomized_quicksort(A,0,A.size()-1,0);
  double time = omp_get_wtime() - start_time;
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
  print_vector(A);
  return 0;
}*/

int main(){
  init_rand_state(1);
  omp_set_num_threads(4);
  omp_set_nested(1);
  vector<long> A;
  map<long,bool> record;
  for (int i = 0; i < 1000; i++){
    long random_number = rand(0)%100000;
    if (record.find(random_number) == record.end()){
      A.push_back(random_number);
      record[random_number] = true;
    }else{
      i--;
    }
  }
  //vector<long> A = {1,10,10,6,8,14,20,10};
  //print_vector(A);
  vector<long> r = vector<long>(A.size(),0);
  double start_time = omp_get_wtime();
  parallel_randomized_quicksort(A,0,A.size()-1,0);
  double time = omp_get_wtime() - start_time;
  //print_vector(A);
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
  return 0;
}
