#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// función que chequea si el número verificador es correcto
int numVerificadorValido(char* cuit) {
	int numerosAMultiplicar[10] = {5, 4, 3, 2, 7, 6, 5, 4, 3, 2};
	int numeroVerificador = 0;
	for(int i = 0; i < 10; i++) {
		// convierto el char a int para poder hacer los productos y las sumas
		int digito = cuit[i] - '0';
		numeroVerificador += digito * numerosAMultiplicar[i]; 
	}
	// ahora me falta tomar el resto de dividir por 11 y restarle 11
	numeroVerificador %= 11;
	numeroVerificador = 11 - numeroVerificador;

	
	//printf("%d", numeroVerificador);
	//printf("%s", numeroVerificadorChar);
	
	char ultimoDigito = cuit[10];
	//printf("%s", ultimoDigito);
	// comparo
	if(numeroVerificador == (ultimoDigito - '0')) {
		printf("%s", "El CUIT ingresado es valido");
	} else {
		cuit[10] = (numeroVerificador + '0');
		printf("El CUIT ingresado no es valido. Su informacion corregida es: %s\n", cuit);
	}
}

void test1() {
	char cuit[11] = "33693450239";
	numVerificadorValido(cuit);
}

void test2() {
	char cuit[11] = "30576124272";
	numVerificadorValido(cuit);
}

int main() {
	test1();
	printf("\n");
	test2();

	return 0;
}






















