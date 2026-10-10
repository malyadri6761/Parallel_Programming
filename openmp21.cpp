#include <iostream>
#include <omp.h>

using namespace std;

int main(){

    const long long N = 100000000;

    long long sum1 = 0;
    
    double serial_start = omp_get_wtime();
    for(long long i=0;i<N;i++){
        sum1+=i;
    }
    double serial_end = omp_get_wtime();


    long long sum2 = 0;

    double parallel_start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum2)
    for(int i=0;i<N;i++)
        sum2+=i;
    double parallel_end = omp_get_wtime();

    double serial = serial_end - serial_start;
    double parallel = parallel_end - parallel_start;

    cout<<"Speed up : "<<serial/parallel;
    return 0;
}