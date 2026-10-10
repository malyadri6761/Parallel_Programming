/*
    OpenMP critical
    ===============
    critical is used when only one thread at a time should execute a 
    paritcular section of code.
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int sum = 0;

    #pragma omp parallel for
    for(int i=0;i<100000;i++){
        #pragma omp critical
        {
            sum++;
        } 
    }
    cout<<"Sum = "<<sum<<endl;
    return 0;
}