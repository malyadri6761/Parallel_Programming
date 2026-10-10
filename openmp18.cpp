/*
    Task : When work is created dynamically and can be executed by any available
    thread.

    This is different from sections.
    Section A
    Section B
    Section C

    task
    ====
    Work can be generated dynamically.
                 Task pool
                /      |      \
            Task 1  Task 2  Task 3
                \      |      /
                available threads
            
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){

    #pragma omp parallel
    {
        #pragma omp single
        {
            for(int i=0;i<8;i++){
                #pragma omp task
                {
                    int id = omp_get_thread_num();
                    cout<<"Task "<<i<<" executed by thread "<<id<<"\n";
                }
            }
        }
    }
    return 0;
}

/*
    Task 0 executed by thread 2
    Task 1 executed by thread 1
    Task 2 executed by thread 3
    Task 3 executed by thread 0
    Task 4 executed by thread 2
    Task 5 executed by thread 3
    Task 6 executed by thread 1
    Task 7 executed by thread 0

    The exact order is not guaranteed.


    Q) Why do we use single?
    Ans : 
        parallel creates the threads.
        single makes one thread responsible for creating the tasks.
        Then the tasks can be executed by any thread in the team.
                    Parallel region
                       │
                  one thread
                       │
                 creates tasks
                       │
       ┌─────────┬─────┴─────┬─────────┐
       ↓         ↓           ↓         ↓
    Task 0    Task 1      Task 2    Task 3
       ↓         ↓           ↓         ↓
    Thread 2  Thread 0    Thread 3  Thread 1


    task vs sections
    =================

    section
    =======
    This distinction is important.
    #pragma omp parallel sections
    {
        #pragma omp section
        task_A();

        #pragma omp section
        task_B();

        #pragma omp section
        task_C();
    }

    You explicitly define the work.

    Tasks
    =====
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < N; i++) {

                #pragma omp task
                process(i);
            }
        }
    }
    You can generate many tasks dynamically.


    Therefore :
    ===========
    sections → fixed number of independent blocks
    tasks    → dynamically generated units of work
    
*/