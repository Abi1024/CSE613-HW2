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
  vector<int> A;
  map<int,bool> record;
  for (int i = 0; i < 32; i++){
    int random_number = rand(0)%1000;
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
  /*vector<int> A;
  map<int,bool> record;
  for (int i = 0; i < 16; i++){
    int random_number = rand(0)%1000;
    if (record.find(random_number) == record.end()){
      A.push_back(random_number);
      record[random_number] = true;
    }else{
      i--;
    }
  }*/
  vector<int> A = {1,8,3,6,10,14,20,10};
  print_vector(A);
  vector<int> r = vector<int>(A.size(),0);
  double start_time = omp_get_wtime();
  par_counting_rank(A,A.size(),5,r,1);
  double time = omp_get_wtime() - start_time;
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
  print_vector(r);
  return 0;
}
