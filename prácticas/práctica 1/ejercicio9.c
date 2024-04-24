#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


/*
El pseudocódigo sería:
- crear el hijo
- Repetir 3 veces:
	- el padre imprime "ping" y su pid
	- manda una señal al hijo
	- el hijo al recibir la señal imprime pongo y su pid
	- manda una señal al padre
- preguntar al usuario si desea repétir el proceso

*/
void handler(int sig) {
    printf("Señal recibida por el padre\n");
}


void pingPong() {

	// creo al proceso hijo
	pid_t pid = fork();

	signal(SIGUSR1, handler); // Registra el manejador de señales

	for (int i = 0; i < 3; ++i) {
			
		if(pid < 0) {
			// si el pid es negativo, hubo un error
			exit(EXIT_FAILURE);
		} else if(pid == 0) {
			// si el pid es cero, estoy en el proceso hijo
			pid_t childID = getpid(); 
			printf("Pong, %d\n", childID);
			kill(getppid(), SIGUSR1); // Envía una señal al proceso padre
			pause(); // Espera hasta que se reciba una señal
		} else {
			// sino, estoy en el proceso padre
			pid_t parentID = getpid();
			printf("Ping, %d\n", parentID);
			kill(pid, SIGUSR1); // envía una señal al proceso hijo
			pause(); // Espera hasta que se reciba una señal
		}
	}
}


int main() {

	pingPong();

	 return 0;
}