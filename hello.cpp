#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
int main(){
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int n = omp_get_num_threads();

        cout<<"Thread Id : "<<thread_id<<'\n';
        cout<<"No.of Threads : "<<n<<'\n';
    }
    return 0;
}