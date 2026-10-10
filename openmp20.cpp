/*
    Performance Measurement
    =======================
    1. Measuring execution time
    2. Sequencial vs Parallel
    
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    const long long N = 100000000;
    long long sum = 0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(long long i=0;i<N;i++)
        sum+=i;
    
    double end = omp_get_wtime();

    cout<<"sum = "<<sum<<"\n";
    cout<<"time = "<<end-start<<"seconds\n";
    return 0;
}