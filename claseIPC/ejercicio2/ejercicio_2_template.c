#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
}

int main(int argc, char const* argv[]) {
  // Completar...
  return 0;
}
