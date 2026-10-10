#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(){

    const int N = 500;

    vector<vector<double>> A(N,vector<double>(N,1.0));
    vector<vector<double>> B(N,vector<double>(N,2.0));

    //sequential
    vector<vector<double>> C1(N,vector<double>(N,0.0));

    double start= omp_get_wtime();

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                C1[i][j]+=A[i][k]*B[k][j];
            }
        }
    }

    double end = omp_get_wtime();

    double sequential_time = end-start;


    //Parallel

    vector<vector<double>> C2(N,vector<double>(N,0.0));

    omp_set_num_threads(4);

    start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for(int i=0;i<N;i++){

        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){

                C2[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    end = omp_get_wtime();

    double parallel_time = end-start;

    cout<<"Speed up : "<< sequential_time/parallel_time;
    return 0;
}