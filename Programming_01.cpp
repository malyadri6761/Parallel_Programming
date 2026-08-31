#include <iostream>
#include <thread>

void work(){
    std::cout<<"Working...\n";
}

int main(){
    std::thread t1(work);
    std::thread t2(work);
    std::thread t3(work);
    std::thread t4(work);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}