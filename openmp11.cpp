#include <iostream>
#include <omp.h>
using namespace std;
int main(){
    int counter = 0;

    #pragma omp paralle for
    for(int i=0;i<20;i++){

        #pragma omp atomic
        counter++;
        printf("Thread %d processed %d\n",omp_get_thread_num(),i);
        
       
    }
    cout<<"\nFinal counter = "<<counter<<endl;
    return 0;
}