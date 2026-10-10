#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;
int main(){
    long long N = 5000000;
    vector<double> data(N,1.23);

    cout<<"Serial Execution : "<<endl;

    double start_serial = omp_get_wtime();
    for(long long i=0;i<N;i++){
        data[i] = sin(data[i])*cos(data[i]);
    }
    double end_serial = omp_get_wtime();

    cout<<"Serial time "<<(end_serial - start_serial);
    fill(data.begin(),data.end(),1.23);

    cout<<"Parallel Execution : "<<endl;
    
    double start_parallel = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0;i<N;i++){
        data[i] = sin(data[i])*cos(data[i]);
    }
    double end_parallel = omp_get_wtime();
    cout<<"Parallel time : "<<end_parallel-start_parallel;
    return 0;
}