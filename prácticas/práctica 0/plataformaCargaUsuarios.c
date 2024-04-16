#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct usuario {
	char nombre[50];
	int edad;
	char cuit[11];
}


int main() {

	// reservo memoria para el comando, sé que el más largo de los dos tiene 25 caracteres
	char* comando = (char*)malloc(25 * sizeof(char)); 
	scanf("%s", comando);
	printf("%s\n", comando);



	return 0;
}