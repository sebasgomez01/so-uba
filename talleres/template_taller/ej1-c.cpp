#include <thread>
#include <iostream>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void f (int i) {
    this_thread::sleep_for((1000ms*i));
    printf("hola, soy el thread: %d\n" , i );
}

int main() {

    for(int i = 0; i < CANT_THREADS; i++) {
        thread t(f,i);
        // opciòn 1
        
        //t.join();
        // opciòn 2
        t.join();
    
    }

    return 0;
}

// new hace que vaya al heap, sino va al stack