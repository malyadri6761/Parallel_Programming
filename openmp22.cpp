/*
    Load Balancing
    ==============
    Distributing work so that all threads have roughly equal amount of 
    work.
    If one thread has much more work than the others, the other threads may 
    finish early and sit idle.

    Problem
    =======
    Thread 0: ████████████████████  20 units
    Thread 1: █████                 5 units
    Thread 2: ████                  4 units
    Thread 3: ██████                6 units

    Excecution Looks like :
    ========================
    Thread 0 ────────────────────────>
    Thread 1 ─────>
    Thread 2 ────>
    Thread 3 ──────>
                ↑
            threads waiting
    Even though 4 threads are being used, the total execution time is determined largely by 
    Thread 0.

*/

// Create an uneven workload
/*
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    const int N = 20;

    #pragma omp parallel for schedule(static) num_threads(4)
    for(int i=0;i<N;i++){
        int id = omp_get_thread_num();
        long long work = 0;
        for(long long j=0;j<(i+1)*1000000LL;j++){
            work+=j;
        }
        cout<<"Thread "<<id<<" completed iteration "<<i<<"\n";
    }
    return 0;
}
*/
/*
        Thread 0 → █████
        Thread 1 → █████████
        Thread 2 → █████████████
        Thread 3 → █████████████████

        i = 0  → small work
        i = 1  → small work
        ...
        i = 19 → much larger work



*/


/*
    Dynamic Scheduling
    ==================
    #pragma omp parallel for schedule(dynamic,1)
    Threads receive a new iteration when they finish their current one.

    Conceptutally:
    =============
    Thread 0 → iteration 0 → gets another
    Thread 1 → iteration 1 → gets another
    Thread 2 → iteration 2 → gets another
    Thread 3 → iteration 3 → gets another
                            ↓
                    free thread gets
                    another iteration
    The heavier iterations naturally get distributed among threads.


    Static:
    =======
    pre-assigned work
        ↓
    possible imbalance

    Dynamic:
    ========
    work assigned as threads become free
        ↓
    better balance


*/

#include <iostream>
#include <omp.h>

using namespace std;


void run(const char* schedule_name){
    const int N = 20;

    double start = omp_get_wtime();

    if(schedule_name[0]=='s'){

        #pragma omp parallel for schedule(static) num_threads(4)
        for(int i=0;i<N;i++){
            long long work = 0;
            for(long long j=0; j<(i+1)*1000000LL;j++){
                work+=j;
            }
            cout<<"Thread : "<<omp_get_thread_num()<<" Static"<<endl;
        }
        
    }
    else{

        #pragma omp parallel for schedule(dynamic,1) num_threads(4)
        for(int i=0;i<N;i++){
            long long work = 0;
            for(long long j=0;j<(i+1)*1000000LL;j++){
                work+=j;
            }
            cout<<"Thread : "<<omp_get_thread_num()<<" Dynamic"<<endl;
        }
        
    }
    double end = omp_get_wtime();
    cout<<schedule_name <<" time = "<<end-start<<" seconds\n";
}
int main(){
    run("static");
    run("dynamic");
    return 0;
}

/*
    Why not always use dynamic?
    ==========================

    Because dynamic scheduling has overhead.
    Imagine 1,000,000 very small iterations.
    static:
    ======
    assign work → done

    dynamic:
    ========
    assign chunk
    thread finishes
    request another chunk
    assign chunk
    thread finishes
    request another chunk
    ...

    That scheduling work costs time.

    Regular workload
    ================
    Each iteration ≈ same cost
        ↓
    schedule(static)

    Irregular workload
    ==================
    Iterations have different costs
        ↓
    schedule(dynamic)

    Irregular workload + want larger initial chunks
    ===============================================
    schedule(guided)

    
*/