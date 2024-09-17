#include <thread>
#include <iostream>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void f () {
    puts ( " Hola! Soy un thread" );
}

int main() {

    for(int i = 0; i < CANT_THREADS; i++) {
        thread t(f);
        // opciòn 1
        //t.join();
        // opciòn 2
        t.detach();
    
    }

    return 0;
}

// new hace que vaya al heap, sino va al stack