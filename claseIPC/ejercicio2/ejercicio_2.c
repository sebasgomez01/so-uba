#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() execlp() dup2() close()
#include <sys/wait.h>

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

void ejecutar_cmd(char* cmd, char* p) {
  execlp(cmd, cmd, p, NULL);
}

// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
  // Cerrar lectura
  close(pipe_fd[READ]);
  // Conectar escritura a stdout
  dup2(pipe_fd[WRITE], STDOUT_FILENO);
  // Ejecutar programa
  ejecutar_cmd("ls", "-al");
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
  // Cerrar escritura
  close(pipe_fd[WRITE]);
  // Conectar lectura a stdin
  dup2(pipe_fd[READ], STDIN_FILENO);
  // Ejecutar programa
  ejecutar_cmd("wc", "-l");
}

int main(int argc, char const* argv[]) {
  int pipe_fd[2];
  pipe(pipe_fd);

  if (fork() == 0) {
    ejecutar_hijo_1(pipe_fd);
  }

  if (fork() == 0) {
    ejecutar_hijo_2(pipe_fd);
  }

  // El padre cierra el fd de escritura
  // Solo así hijo_2 va a recibir EOF cuando hijo_1 termina
  close(pipe_fd[WRITE]);

  // Esperamos que terminen los hijos antes de terminar el padre
  wait(NULL);
  wait(NULL);

  return 0;
}
