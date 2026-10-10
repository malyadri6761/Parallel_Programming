// Practical Example : Parallel Vector Addition

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(){
    const int N = 1000000;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);

    for(int i=0;i<N;i++){
        A[i] = i;
        B[i] = 2*i;
    }
    double start1 = omp_get_wtime();
    for(int i=0;i<N;i++){
        C[i] = A[i] + B[i];
    }
    double end1 = omp_get_wtime();

    double start_time = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<N;i++){
        C[i] = A[i] + B[i];
    }
    double end_time = omp_get_wtime();

    cout<< C[100]<<endl;

    double serial = (end1-start1);
    double parallel = (end_time - start_time);

    cout<<"Serial time : "<<serial<<endl;
    cout<<"Parallel time : "<<parallel<<endl;
    cout<<"Speed up : "<<(serial/parallel)<<endl;

    return 0;
}