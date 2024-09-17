#include <thread>
#include <iostream>
#include <semaphore>

//binary_semaphore permiso_a(0);
//binary_semaphore permiso_b(0);
sem_t permiso_a;
permiso_a.init(0);
sem_t permiso_b;
permiso_a.init(0);


#define MSG_COUNT 5

using namespace std;


void f1_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (A)\n";
        this_thread::sleep_for(100ms);
    }
}

void f1_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (B)\n";
        this_thread::sleep_for(100ms);
    }
}

void f2_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (A)\n";
        this_thread::sleep_for(100ms);
    }
}

void f2_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (B)\n";
        this_thread::sleep_for(100ms);
    }
}

void f1() {
    f1_a();
    permiso_b.release();
    permiso_a.acquire();
    f1_b();
}

void f2() {
    f2_a();
    permiso_a.release();
    permiso_b.release();
    f2_b();
}

int main() {
    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    return 0;
}