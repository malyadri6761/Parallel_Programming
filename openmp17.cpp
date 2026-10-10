/*
    single - Execute this block by one thread.
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        #pragma omp single
        {
            cout<<"Only one thread executes this.\n";
            cout<<"Exectuing thread = "<<id<<"\n";
        }
        cout<<"Thread : "<<id<<" continues.\n";
    
    }
    return 0;
}


/*
    Why use single?
    ===============
    Suppose every thread needs to use some data, but only one thread should initialize it:

    #pragma omp parallel
    {
        #pragma omp single
        {
            //Load data once    
        }
        // All threads use the data
    }
    This prevents all threads from unnecessarily loading the same thing.


    single has an implicit barrier
    =============================
    #pragma omp parallel
    {
        #pragma omp single
        {
            //executed by one thread
        }
        
        //threads continue
    }
    This is an implicit barrier after the single block.
    conceptually:
        Thread 0 ───────────────┐
        Thread 1 ── SINGLE ─────┤
        Thread 2 ───────────────┤── BARRIER → continue
        Thread 3 ───────────────┘
    
    You can remove this synchronization with : #pragma omp single nowait
    But then other threads are allowed to continue immediately.


    | Feature          | `sections`                                       | `single`                  |
    | ---------------- | ------------------------------------------------ | ------------------------- |
    | Purpose          | Different tasks                                  | One shared task           |
    | Execution        | Each section once                                | Block once                |
    | Threads          | Different threads can execute different sections | One thread executes block |
    | Example          | Load + process + save                            | Initialize data           |
    | Implicit barrier | Yes                                              | Yes                       |



*/