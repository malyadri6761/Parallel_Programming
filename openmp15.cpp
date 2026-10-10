/*
    sections and single
    ===================
    These are used when different threads need to perform different pieces of work.

    sections
    ========
    It allows different threads to execute different code blocks.

*/

#include <iostream>
#include <omp.h>

using namespace std;
int main(){
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            cout<<"Task A -> Thread"<<omp_get_thread_num()<<"\n";
        }

        #pragma omp section
        {
            cout<<"Task B -> Thread"<<omp_get_thread_num()<<"\n";
        }
        #pragma omp section
        {
            cout<<"Task C -> Thread"<<omp_get_thread_num()<<"\n";
        }
    }
    return 0;
}

/*
    Task A -> Thread 0
    Task B -> Thread 2
    Task C -> Thread 1

    The exact thread assignment and output order are not guaranteed.
   
            Parallel Region
                   |
       +-----------+-----------+
       |           |           |
    Section A   Section B   Section C
       |           |           |
   Thread 0    Thread 1    Thread 2

   Each section is executed once by one thread.
   

*/