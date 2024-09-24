#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1


void procesoHijo(int descriptores[2]) {
    // mando mensaje al padre
    //char mensaje[10] = "Hola papá";
    int mensaje = 10;
    write(descriptores[WRITE], &mensaje, sizeof(mensaje));
    //close(descriptores[WRITE]);
    printf("print del proceso hijo\n");
}

void procesoPadre() {
    int descriptores[2];
    pipe(descriptores);

    pid_t pidHijo = fork();
    
    if(pidHijo == 0) {
        procesoHijo(descriptores);
    } else {
        
        // leo mensaje del hijo
        int mensaje;
        read(descriptores[READ], &mensaje, sizeof(mensaje));
        close(descriptores[READ]);
        printf("El mensaje que leyó el padre es: \n");
        printf("%d\n", mensaje);

        
    }
}

int main(int argc, char **argv) {

    procesoPadre();

    return 0;	
}
