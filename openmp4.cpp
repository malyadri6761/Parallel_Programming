/*
    schedule(static) - loop iterations are divided among threads.
    Iterations:  0  1  2  3  4  5  6  7  8  9  10 11
    Thread 0:    0  1  2
    Thread 1:             3  4  5
    Thread 2:                         6  7  8
    Thread 3:                                     9  10 11

    This is OpenMp parallelism, specifically loop/work-sharing.

    schedule(static)
    ===================================================================
        Divide the loop iterations among threads before exection begins.
        The assignment does not dynamically change while the program runs.

    schedule(static,chunk_size)
    ======================================================================
        you can explicitly specify the chunk size:
        #pragma omp parallel for schedule(static,2)
        for(int i=0;i<12;i++){
            //work
        }
        chunk_size = 2
        ===============
        OpenMP creates
        ================
        [0,1]
        [2,3]
        [4,5]
        [6,7]
        [8,9]
        [10,11]

        This chunks are assigned to threads : 
        ======================================
        Thread 0 → [0,1]     [8,9]

        Thread 1 → [2,3]     [10,11]

        Thread 2 → [4,5]

        Thread 3 → [6,7]

        The important difference is that with an explicit chunk size, chunks
        are distributed cyclically among threads.

        Static vs default static
        ===============================
        schedule(static)
        =================
        #pragma omp parallel for schedule(static) - usually divides the entire iteration
        space into approximately equal contiguous protions.
        T0 → 0  1  2
        T1 → 3  4  5
        T2 → 6  7  8
        T3 → 9 10 11
        

        schedule(static,1)
        ====================
        #pragma omp parallel for schedule(static,1)
        uses chunks of one iterations : 
        T0 → 0, 4, 8
        T1 → 1, 5, 9
        T2 → 2, 6, 10
        T3 → 3, 7, 11


        Why use satatic?
        Static scheduling is particularly when every iteration has approximately the
        same computational cost.

        Example : 
                    #pragma omp parallel for schedule(static)
                    for(int i=0;i<N;i++)
                        C[i] = A[i]+B[i];
                    
                    Every iteration performs roughly the same amount of work:
                    C[0] = A[0] + B[0]
                    C[1] = A[1] + B[1]
                    ...

        Therefore : 
            Equal work
                ↓
            Equal distribution
                ↓
            Good load balance
                ↓
            Low scheduling overhead
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main(){
    const int N = 20;
    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);

    for(int i=0;i<N;i++){
        A[i] = i;
        B[i] = 2*i;
    }

    #pragma omp parallel for schedule(static)
    for(int i=0;i<N;i++){
        int thread_id = omp_get_thread_num();
        C[i] = A[i] + B[i];
        printf("Thread %d-> C[%d] = %d\n",thread_id,i,C[i]);
    }


    cout<<"\nFinal Array : \n";
    for(int i=0;i<N;i++){
        cout<<C[i]<<" ";
    }
    cout<<endl;
    return 0;
}