/*
    Practical Example : Recursive Fibonacci
*/

#include <iostream>
#include <omp.h>

using namespace std;

int fib(int n){
    if(n<=1)
        return n;
    
    int x,y;

    #pragma omp task shared(x)
    x = fib(n-1);

    #pragma omp task shared(y)
    y = fib(n-2);

    #pragma omp taskwait
    return x+y;

}
int main(){
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(10);
        }
    }
    cout<<"Fibonacci = "<<result<<"\n";
    return 0;
}

/*
    barrier   → thread synchronization
    taskwait  → task synchronization
*/