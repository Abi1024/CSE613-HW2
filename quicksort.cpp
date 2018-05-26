#include <iostream>
#include <vector>
#include "quicksort.h"
#include "prefix_sum.h"
#include <omp.h>
using namespace std;
float start_time;

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

void print_vector(const vector<float>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

int parallel_partition(vector<float>& A, int q, int r, float x){
  cout << "in parallel partition" << endl;
  int n = r - q + 1;
  if (n == 1){
    return q;
  }
  cout << "n: " << n << endl;
  vector<float> B = vector<float>(n);
  vector<int> lt = vector<int>(n, 0);
  vector<int> gt = vector<int>(n, 0);
  #pragma omp parallel for
  for(int i = 0; i < n; i++){
    B[i] = A[q+i];
    if (B[i] < x){
      lt[i] = 1;
    }else if (B[i] > x){
      gt[i] = 1;
    }
  }
  cout << "B:" << endl;
  print_vector(B);
  //print_vector(lt);
  //print_vector(gt);
  parallel_prefix_sum(lt);
  parallel_prefix_sum(gt);
  print_vector(lt);
  print_vector(gt);
  int k = q + lt[n-1];
  int l = r+1- gt[n-1];
  cout << "k: " << k << endl;
  cout << "l: " << l << endl;
  A[k] = x;
  #pragma omp parallel for
  for (int i = 0; i < n; i++){
    if (B[i] < x){
      A[q + lt[i]-1] = B[i];
    }else if (B[i] > x){
      A[l + gt[i] - 1] = B[i];
    }else{
      A[k + (i-lt[i]-gt[i])] = B[i];
    }
  }
  //print_vector(A);
  return k;
}

void parallel_randomized_quicksort(vector<float>& A, int q, int r, int m, int thread_ID){
  cout << "Calling parallel_randomized_quicksort on size: " << (r-q+1 )<< " thread num: " << thread_ID << endl;
  int n = r-q + 1;
  if (n <= m){
    //cout << "Calling insertion sort" << endl;
    for (int i = 1; i < n; i++){
      int j = i;
      //cout << "dumped?" << endl;
      while ((j > 0) && (A[q+j-1] > A[q+j])){
        //cout << "o";
        float temp = A[q+j-1];
        A[q+j-1] = A[q+j];
        A[q+j] = temp;
        j--;
      }
    }
  }else{
    int random_index = rand(thread_ID) % n;
    float random_number = A[q+random_index];
    //cout << "random number: " << random_number << endl;
    //cout << "Array before partition:" << endl;
    //print_vector(A);
    int k = parallel_partition(A,q,r,random_number);
    //cout << "k: " << k << endl;
    //cout << "Array after partition:" << endl;
    //print_vector(A);

    #pragma omp task default(shared)
    parallel_randomized_quicksort(A,q,k-1,m,omp_get_thread_num());

    #pragma omp task default(shared)
    parallel_randomized_quicksort(A,k+1,r,m,omp_get_thread_num());

    #pragma omp taskwait
  }
}
