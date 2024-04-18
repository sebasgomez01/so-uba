#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void bart() {
	printf("Bart\n");
	exit(EXIT_SUCCES);
}

void lisa() {
	printf("Lisa\n");
	exit(EXIT_SUCCES);
}

void maggie() {
	printf("Maggie\n");
	exit(EXIT_SUCCES);
}

void homero() {
	printf("Homero\n");

	// creo a Bart
	pid_t pid = fork();
	if(pid < 0) {
		// si el pid es negativo, hubo un error
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		// si el pid es cero, estoy en el proceso hijo
		bart();
	} else {
		// sino, estoy en el proceso padre
	}

	// creo a Lisa
	pid = fork();
	if(pid < 0) {
		// si el pid es negativo, hubo un error
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		// si el pid es cero, estoy en el proceso hijo
		lisa();
	} else {
		// sino, estoy en el proceso padre
	}

	// creo a Maggie
	pid = fork();
	if(pid < 0) {
		// si el pid es negativo, hubo un error
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		// si el pid es cero, estoy en el proceso hijo
		maggie();
	} else {
		// sino, estoy en el proceso padre
	}

}

void abraham() {
	printf("Abraham\n");

	// creo a Homero
	pid_t pid = fork();
	if(pid < 0) {
		// si el pid es negativo, hubo un error
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		// si el pid es cero, estoy en el proceso hijo
		homero();
	} else {
		// sino, estoy en el proceso padre, debo esperar a qué termine Homero para finalizar
		int status;
		wait(&status);
		// según entiendo, wait guarda en status la información sobre el cambio que se produjo en el proceso
		// entonces ahora tengo en status la información de si el proceso terminó o no
		// WIFEXITED(status) me devuelve true si el proceso hijo terminó normalmente
		if(WIFEXITED(status)) {
			exit(EXIT_SUCCES);
		} else {
			exit(EXIT_FAILURE);
		}
	}
}


int main() {

	abraham();

	return 0;
}