/*
================================
    Parallel Reduction 
================================


for(int i=0;i<n;i++)
    sum+=A[i];

You can't just #pragma omp parallel
because multiple threads modify the value sum.

The solution is reduction

#pragma omp parallel for reduction(+:sum)
Thread 0 → local_sum0
Thread 1 → local_sum1
Thread 2 → local_sum2
Thread 3 → local_sum3
                 |
                 ↓
       sum = local_sum0
           + local_sum1
           + local_sum2
           + local_sum3

*/
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(){
    const int N = 10000000;

    vector<int> A(N);
    

    for(int i=0;i<N;i++){
        A[i] = i*2;
    }

    long long sum = 0;
    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<N;i++)
        sum+=A[i];
    double end_time = omp_get_wtime();

    cout<<"Computation time : "<<(end_time - start_time)<<"ms";
    return 0;

}