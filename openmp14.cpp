/*
    Reduction : Most useful OpenMP features for parallel computation.

    It is especially useful for projects : K-Means, PageRank, Matrix Operations, and CUDA.

    Problem : Calculating a Sum using parallelize the loop : 
    =======================================================
    #pragma omp parallel for
    for(int i=01;i<=100000;i++){
        sum+=i;
    }
    This is incorrect because multiple threads update sum concurrently, causing 
    a race condition.


    The above problem fixing using reduction.



*/
#include <iostream>
#include <omp.h>

using namespace std;
int main(){

    long long sum =0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=1;i<=100000;i++)
        sum+=i;
    cout<<"Sum = "<<sum<<'\n';
    return 0;
}


/*
    #pragma omp parallel for reduction(+:sum)
    ========================================
    parallel for - distributes loop iterations among threads
    reduction - creates private reduction values and combines them.
    + - specifies the addition operation.
    sum - the variable being reduced.

    For a sum reduction, each thread's private value starts at the additive 
    identity, 0 rather than copying the original sum.

    Operation   Example                 Initial Private Value
    =========   =======                 =====================
    Sum         reduction(+:sum)         0
    Product     reduction(*:product)     1
    Maximum     reduction(max:max_val)   Lowest representable value
    Minimum     reduction(min:min_val)   Highest representable value
    Logical AND reduction(&:flag) for    All bits set
                integer bitwise AND

    For max and min, the exact identity depends on the variable's type and
    the reduction rules. OpenMP also supports logical and bitwise reduction operators.
    
*/