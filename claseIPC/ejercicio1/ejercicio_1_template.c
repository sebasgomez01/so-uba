#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include "dado.h"    // tirar_dado()

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };
// Constants 0 and 1 for LESTER and ELIZA
enum { LESTER, ELIZA };

// Variables globales

void lester() {
  // Tiro el dado
  // Le informo el resultado a Humberto
}

void eliza() {
  // Tiro el dado
  // Le informo el resultado a Humberto
}

int main(int argc, char const* argv[]) {
  // Creo los pipes

  // Creo a Lester

  // Creo a Eliza

  // Recibo el dado de Lester

  // Recibo el dado de Eliza

  // Anuncio al ganador

  return 0;
}
