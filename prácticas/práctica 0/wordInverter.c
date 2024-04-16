#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// función que recibe dos char y los swapea, esto lo uso para invertir la palabra
void charSwap(char a, char b) {
	if(a == b) {
		return;
	} else {
		char c = a;
		a = b;
		b = c;	
	}
	
}

// función que convierte una parabra en mayúscula en el caso de que la longitud sea mayor a n
char* wordToUppercaseAndInvert(char* word, int n) {
	int longitud = strlen(word);
	if(longitud > n) {
		// convierto a mayúscula
		for(int i = 0; i < longitud; i++) {
			word[i] = toupper(word[i]);
		}	

		// invierto la palabra
		for(int i = 0; i < longitud / 2; i++) {
			charSwap(word[i], word[longitud - 1 - i]);
		}
	}
	return word;
}

void test1() {
	char word[] = "hola";
	int n = 3;
	wordToUppercaseAndInvert(word, n);
	printf("%s", "La palabra luego de aplicarle la función es: ");
	printf("%s", word);
}


int main() {

	test1();

	// declaro las variables para guardar los parámetros
	int n;
	char* frase;

    // Reservo memoria para la cadena
    frase = (char*)malloc(100 * sizeof(char)); // Supongo que la longitud máxima de la cadena es de 100 caracteres

    // Compruebo si la asignación de memoria fue exitosa
    if (frase == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return 1; // Salimos del programa con un código de error
    }

    // leo y guardo los argumentos indtroducidos por consola
    printf("%s", "\n Introduzca un número: ");
	scanf("%d", &n);

	// limpio el buffer de entrada
	getchar();

	printf("%s", "Introduzca una frase: ");
	fgets(frase, 100, stdin);

	printf("La frase es: %s\n", frase);
	printf("El número es: %d\n", n);

	return 0;
}