
#include <thread>
#include <iostream>
#include <unistd.h>
#include <mutex>

#define CANT_THREADS 10

using namespace std;
mutex m;

void f ( int i  ) {
    m.lock();
        printf("Hola, soy el thread %d \n", i);
        printf("Chau! Saludos desde: %d \n", i);
    m.unlock();
}


int main() {

    for(int i = 0; i < CANT_THREADS; i++) {
        thread t(f, i);
        // opciòn 1
        t.join();
        // opciòn 2
        //t.detach();
    
    }

    return 0;
}
