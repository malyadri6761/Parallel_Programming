/*
    Race Condition
    ==============
    atomic - Protects one memory operation from race condition.
    The key difference : 
        critical -> Protects a block of code.
        atomic -> Protects a single memory update.
        
*/
#include <iostream>
#include <omp.h>

using namespace std;

int main(){

    int sum = 0;
    
    #pragma omp parallel for
    for(int i=0;i<100000;i++){
        #pragma omp atomic
        {
            sum++;
        }
    }
    cout<<"Sum : "<<sum;
    return 0;

    /*
        Thread 0 → [sum++]
        Thread 1       waits
        Thread 2       waits
        Thread 3       waits

        Thread 0 → finishes

        Thread 2 → [sum++]
        ...

        The important point is that the update itself is protected.

        | Feature  | `critical`          | `atomic`         |
        | -------- | ------------------- | ---------------- |
        | Protects | Code block          | Memory operation |
        | Example  | Multiple statements | `sum++`          |
        | Scope    | Larger              | Very small       |
        | Overhead | Generally higher    | Generally lower  |
        | Good for | Complex operations  | Simple updates   |


        Example : This needs critical.
        =============================
        #pragma omp critical
        {
            sum += value;
            count++;
            total += value * 2;
        }

        While this is a good use of atomic
        ==================================
        #pragma omp atomic
        sum += value;
    */
}
