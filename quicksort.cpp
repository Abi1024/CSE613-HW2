#include <iostream>
#include <vector>
#include "quicksort.h"
#include "prefix_sum.h"
#include <omp.h>
using namespace std;

void print_vector(vector<int>& A){
  for (unsigned int i = 0; i < A.size(); i++){
    cout << A[i] << " ";
  }
  cout << endl;
}

int parallel_partition(vector<int>& A, int q, int r, int x){
  int n = r - q + 1;
  if (n == 1){
    return q;
  }
  //cout << "n: " << n << endl;
  vector<int> B = vector<int>(n);
  vector<int> lt = vector<int>(n, 0);
  vector<int> gt = vector<int>(n, 0);
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
  parallel_prefix_sum(lt);
  parallel_prefix_sum(gt);
  //print_vector(lt);
  //print_vector(gt);
  int k = q + lt[n-1];
  A[k] = x;
  for (int i = 0; i < n; i++){
    if (B[i] < x){
      A[q + lt[i]-1] = B[i];
    }else if (B[i] > x){
      A[k + gt[i]] = B[i];
    }
  }
  //print_vector(A);
  return k;
}

void parallel_randomized_quicksort(vector<int>& A, int q, int r, int thread_ID){
  //cout << "Calling parallel_randomized_quicksort" << endl;
  int n = r-q + 1;
  if (n <= 32){
    //cout << "Calling insertion sort" << endl;
    for (int i = 1; i < n; i++){
      int j = i;
      while ((j > 0) && (A[q+j-1] > A[q+j])){
        int temp = A[q+j-1];
        A[q+j-1] = A[q+j];
        A[q+j] = temp;
        j--;
      }
    }
  }else{
    int random_index = rand(thread_ID) % n;
    int random_number = A[q+random_index];
    //cout << "random number: " << random_number << endl;
    //cout << "Array before partition:" << endl;
    //print_vector(A);
    int k = parallel_partition(A,q,r,random_number);
    //cout << "k: " << k << endl;
    //cout << "Array after partition:" << endl;
    //print_vector(A);
    #pragma omp parallel
    {
      #pragma omp single nowait
      {
        parallel_randomized_quicksort(A,q,k-1,omp_get_thread_num());
      }
      #pragma omp single nowait
      {
        parallel_randomized_quicksort(A,k+1,r,omp_get_thread_num());
      }
    }
  }
}
