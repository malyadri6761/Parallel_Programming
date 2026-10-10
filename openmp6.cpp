/*
    schedule(guided)
    ================

    It is another OpenMp loop-scheduling strategy, designed to 
    balance load while reducing overhead compared with very 
    small dynamic chuks.

    Q) What is guided do?
    Ans : OpenMp initially gives threads larger chunks.
          As the no.of remining iterations decreases, the chunks become smaller.
    
          Conceptually:
            Remaining work
                ↓

            Large chunk
            ████████████████

                ↓

            Medium chunk
            ████████

                ↓

            Smaller chunk
            ████

                ↓

            Small chunk
            ██

        Example : 20 iterations
            T0 → [0 ... 4]
            T1 → [5 ... 9]
            T2 → [10 ... 14]
            T3 → [15 ... 19]
        
            Then as threads finish and more work remains, OpenMp assigns
            progressively smaller chunks.

            The exact chunk distribution is implementation-dependent, 
            so don't assume those exact ranges.


        Dynamic : #pragma omp parallel for schedule(dynamic,1)
        ======================================================
        Uses approximately the same chunk size throghout:
        [0]
        [1]
        [2]
        [3]
        [4]
        [5]
        ...
        This gives good load balancing but can significant scheduling overhead.

        Guided : #pragma omp parallel for schedule(guided)
        ==================================================
        Starts with larger chuks : 
        [0 1 2 3 4]
        [5 6 7]
        [8 9 10]
        ...  and eventually uses smaller chunks.

        dynamic
            ↓
        constant-size chunks

        guided
            ↓
        large → medium → small chunks


    Guided With a minimum chunk size
    ================================
        #pragma omp parallel for schedule(guided,2) - The 2 means OpenMp should
        not normally make chunks samller than approximately 2 iterations.

        Conceptually : 
            Large chunks
                ↓
            Medium chunks
                ↓
            2 iterations
                ↓
            2 iterations
        
    | Schedule    | Behavior                                | Good for                                     |
    | ----------- | --------------------------------------- | -------------------------------------------- |
    | `static`    | Fixed distribution                      | Uniform work                                 |
    | `dynamic,1` | Small chunks assigned as threads finish | Highly irregular work                        |
    | `dynamic,4` | 4 iterations/chunk                      | Irregular work with lower overhead           |
    | `guided`    | Large → small chunks                    | Irregular work + reduced scheduling overhead |
    | `guided,2`  | Large → small, minimum ~2               | Fine control                                 |
  

                        OpenMP Scheduling

                         Loop
                          │
          ┌───────────────┼───────────────┐
          ↓               ↓               ↓
       static          dynamic          guided
          │               │               │
      fixed work      same-size       decreasing
      assignment        chunks          chunks
          │               │               │
      low overhead     better load     balance +
                       balancing       lower overhead
*/


#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
int main(){
    const int N=20;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);

    for(int i=0;i<N;i++){
        A[i]= i;
        B[i] = 2*i;
    }

    #pragma omp parallel for schedule(dynamic,2)
    for(int i=0;i<N;i++){
        int thread_id = omp_get_thread_num();
        C[i] = A[i] + B[i];
        printf("Thread %d -> i = %d -> C[%d] = %d \n",thread_id,i,i,C[i]);
    }
    cout<< "\nFinal array : \n";
    for(int i=0;i<N;i++)
        cout<<C[i]<<" ";
    return 0;
}