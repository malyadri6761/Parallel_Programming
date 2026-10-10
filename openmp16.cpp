/* 
    Practical : Example of sections

    This is useful when you have a small number of independent tasks.
*/

#include <iostream>
#include <omp.h>

using namespace std;

void load_data(){
    cout<<"Loading data ...\n";
}

void process_data(){
    cout<<"Processing data ...\n";
}

void save_data(){
    cout<<"Saving data ...\n";
}

int main(){

    #pragma omp prallel sections
    {
        #pragma omp section
        load_data();
        #pragma omp section
        process_data();
        #pragma omp section
        save_data();
    }
    return 0;




}