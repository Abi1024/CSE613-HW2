#include <iostream>
#include <fstream>
#include <vector>
#include "quicksort.h"
#include <omp.h>
#include "error.h"
using namespace std;
double start_time;

void print_vector(const vector<int>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

void print_vector(const vector<unsigned int>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

void print_vector(const vector<unsigned long long>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

void print_vector(const vector<double>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

vector<int> parallel_partition(vector<double>& A, int q, int r, double x, bool verbose){
  vector<int> result(2);
  int n = r - q + 1;
  if (n == 1){
    result[0] = q;
    result[1] = q;
    cout << "MAJOR ERROR" << endl;
    exit(1);
    return result;
  }
  if (verbose){
    error[omp_get_thread_num()] << "in parallel partition, n: " << n << " q: " << q << " r: " << r << " threadID: " <<  omp_get_thread_num() << endl;
  }
  //
  vector<double> B = vector<double>(n);
  vector<int> lt = vector<int>(n, 0);
  vector<int> gt = vector<int>(n, 0);
  //printf("setup vectors, thread num: %d \n",omp_get_thread_num());
  //#pragma omp parallel for schedule(dynamic,4096)
  for(int i = 0; i < n; i++){
    B[i] = A[q+i];
    if (B[i] < x){
      lt[i] = 1;
    }else if (B[i] > x){
      gt[i] = 1;
    }
  }
  //cout << "B:" << endl;
  //print_vector(B);
  //print_vector(lt);
  //print_vector(gt);
  if (verbose){
    error[omp_get_thread_num()] << "entering prefix sum, threadID: " <<  omp_get_thread_num() << endl;
  }
  parallel_prefix_sum(lt);
  parallel_prefix_sum(gt);
  if (verbose){
    error[omp_get_thread_num()] << "Done with prefix sum, threadID: " <<  omp_get_thread_num() << endl;
  }
  //print_vector(lt);
  //print_vector(gt);
  result[0] = q + lt[n-1];
  result[1] = r+1- gt[n-1];
  //cout << "k: " << k << endl;
  //cout << "l: " << l << endl;
  //A[result[0]] = x;
  //#pragma omp parallel for schedule(dynamic,4096)
  for (int i = 0; i < n; i++){
    if (B[i] < x){
      A[q + lt[i]-1] = B[i];
    }else if (B[i] > x){
      A[result[1] + gt[i] - 1] = B[i];
    }else{
      A[result[0] + (i-lt[i]-gt[i])] = B[i];
    }
  }
  //print_vector(A);
  if (verbose){
      error[omp_get_thread_num()] << "Done with parallel partition, threadID: " <<  omp_get_thread_num() << endl;
  }
  return result;
}

void parallel_randomized_quicksort(vector<double>& A, int q, int r, int m, int thread_ID, bool verbose, int depth){
  int n = r-q + 1;
  if (q < 0){
    cout << "ERROR" << endl;
  }
  if (verbose){
      error[thread_ID] << "Calling quicksort on n: " << n << " with threadID: " <<  omp_get_thread_num() << endl;
  }
  cout << "Calling quicksort on n: " << n << " with threadID: " << thread_ID << endl;
  if ((depth > 5)||(n <= m)){
    if (verbose){
      error[thread_ID] << "calling insertion sort on n: " << n << " with threadID: " <<  omp_get_thread_num() << endl;
    }
    cout << "Calling insertion sort on n: " << n << " with threadID: " << thread_ID << endl;
    for (int i = 1; i < n; i++){
      int j = i;
      //cout << "dumped?" << endl;
      while ((j > 0) && (A.at(q+j-1) > A.at(q+j))){
        //cout << "o";
        double temp = A.at(q+j-1);
        A.at(q+j-1) = A.at(q+j);
        A.at(q+j) = temp;
        j--;
      }
    }
    cout << "Ending insertion sort on n: " << n << " with threadID: " << thread_ID << endl;
  }else{
    if (verbose){
      error[thread_ID] << "performing the recursion on n: " << n << " with threadID: " <<  thread_ID << endl;
    }
    int random_index = rand(thread_ID) % n;
    double random_number = A.at(q+random_index);
    if (verbose){
      error[thread_ID] << "generated random number on n: " << n << " with threadID: " <<  thread_ID << endl;
    }
    //cout << "random number: " << random_number << endl;
    //error[0] << "random: " << random_number << endl;
    //cout << "Array before partition:" << endl;
    //print_vector(A);

    //vector<int> partition = parallel_partition(A,q,r,random_number,verbose);
    vector<int>partition = {q+n/2,q+n/2+1};
    cout << "Entering the recursion with n: " << n << " with threadID: " << thread_ID << endl;
    //cout << "Array after partition:" << endl;
    //print_vector(A);
    if (verbose){
      error[thread_ID] << "done with parallel partition on n: " << n << " with threadID: " <<  thread_ID << endl;
    }
    #pragma omp task default(none) shared(A) firstprivate(partition,m,verbose,depth,q,r)
    parallel_randomized_quicksort(A,q,partition[0]-1,m,omp_get_thread_num(),verbose, depth+1);

    #pragma omp task default(none) shared(A) firstprivate(partition,m,verbose,depth,q,r)
    parallel_randomized_quicksort(A,partition[1],r,m,omp_get_thread_num(),verbose, depth+1);

    if (verbose){
      error[thread_ID] << "waiting on quicksort on n: " << n << " with threadID: " <<  omp_get_thread_num() << endl;
    }

    #pragma omp taskwait
    //cout << "Ending quicksort on n: " << n << " with threadID: " <<  omp_get_thread_num() << endl;
  }
  if (verbose){
    error[omp_get_thread_num()] << "Ending quicksort on n: " << n << " with threadID: " <<  omp_get_thread_num() << endl;
  }
  cout << "Exiting quicksort on n: " << n << " with threadID: " << thread_ID << endl;
}
