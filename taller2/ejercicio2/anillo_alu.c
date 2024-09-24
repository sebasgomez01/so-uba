#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

int generate_random_number(){
	return (rand() % 50);
}


void procesoNoInicial(int pipesAnillo[][2], int id, int cantProcesos) {
	//printf("soy un proceso no inicial \n");
	
	while(1) {
		int mensaje;
		read(pipesAnillo[(id) % cantProcesos][PIPE_READ], &mensaje, sizeof(mensaje));
		printf("soy el proceso %d, y recibí el mensaje: %d \n", id, mensaje);
		mensaje++;
		write(pipesAnillo[(id+1) % cantProcesos][PIPE_WRITE], &mensaje, sizeof(mensaje));
	}
	
	exit(0);
}

void procesoInicial(int descriptores[2], int pipesAnillo[][2], int id, int cantProcesos) {

	int mensaje;
	read(descriptores[PIPE_READ], &mensaje, sizeof(mensaje));
	printf("Soy el proceso inicial, mi id es %d, y el número enviado por el padre es: %d\n", id, mensaje);
	mensaje++;

	write(pipesAnillo[(id+1) % cantProcesos][PIPE_WRITE], &mensaje, sizeof(mensaje));

	int numeroSecreto = 50;
	while(mensaje < numeroSecreto) {
		read(pipesAnillo[(id) % cantProcesos][PIPE_READ], &mensaje, sizeof(mensaje));
		printf("soy el proceso %d y recibí el mensaje: %d\n", id, mensaje);
		write(pipesAnillo[(id+1) % cantProcesos][PIPE_WRITE], &mensaje, sizeof(mensaje));
	}

	write(descriptores[PIPE_WRITE], &mensaje, sizeof(mensaje));	

	exit(0);
}

int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
    
    /* código del proceso padre */
	
	// creo el para comunicarme con el proceso inicial
	int pipePadreAHijo[2];
	pipe(pipePadreAHijo);

	// creo los pipes para el anillo
	int pipesAnillo[n][2];
	for(int i = 0; i < n; i++) {
		pipe(pipesAnillo[i]);
	} 

	// creo los n hijos
	pid_t pidsHijos[n];
	for (int i = 0; i < n; i++) {
		pidsHijos[i] = fork();

		if(pidsHijos[i] == 0 && i == start) {
			printf("soy el proceso: %d\n", i);
			procesoInicial(pipePadreAHijo, pipesAnillo, i, n);
		} else if(pidsHijos[i] == 0) {
			procesoNoInicial(pipesAnillo, i, n);
		}
	}

	// envio el mensaje inicial al iésimo hijo
	write(pipePadreAHijo[PIPE_WRITE], &buffer, sizeof(buffer));

	int numeroFinal;
	read(pipePadreAHijo[PIPE_READ], &numeroFinal, sizeof(numeroFinal));

	printf("Soy el padre, el ciclo terminó y el número final que recibí es %d: \n", numeroFinal);

}
