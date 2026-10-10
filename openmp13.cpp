/*
    
    Suppose we have two stages : 
    Phase 1: calculate data
            ↓
        barrier
            ↓
    Phase 2: use calculated data



*/
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int data[4] = {0};

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();

        //Phase 1
        data[id] = id*10;
        cout<<"Thread "<<id<<" calculated data["<<id<<"]\n";

        #pragma omp barrier
        //Phase 2
        #pragma omp critical
        {
            cout<<"Thread "<<id<<" sees : ";
            for(int i=0;i<4;i++){
                cout<<data[i]<<" ";
            }
            cout<<"\n";
        }


    }
    return 0;
}


/*
    Important distinction
    =====================
    barrier does not protect a variable from race conditions.
    It only synchronizes when threads continue.

    #pragma omp barrier
    ===================
    means : "Wait here until everyone arrives."

    #pragma omp critical
    ====================
    means : "Only one thread can execute this block at a time."

    #pramge omp atomic
    ==================
    means : "Perform this particular memory update atomically."


    


*/