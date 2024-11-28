** EJERCICIO 16 

En cierto sistema los usuarios acumulan créditos y eso les permite ejecutar diversas funciones, que tienen un costo que va variando. 
El siguiente fragmento de código es el encargado de ejecutar la función f() si los créditos que le quedan al usuario superan el costo de la función. La variable costo
contiene el costo que el sistema le asignó a la función f() y creditos es un puntero a la cantidad de
créditos que tiene el usuario.

void seleccionar_funcion(unsigned int opcion) {
  func (*funciones)[1000] = [ &f1, &f2, ..., &f1000 ];
  int costos[1000] = [10, 100, 10000, 100000, ..., 10000000];
  if (opcion>=1000) { return; // error };
  usuario *usuario_actual = get_user();
  creditos = usuario_actual->creditos;
  return ejecutar_si_quedan_creditos(&creditos, costos[opcion-1], funciones[opcion-1]);
}

void ejecutar_si_quedan_creditos(int *creditos, int costo, func *f) {
  unsigned int saldo = (*creditos) - costo;
  if (saldo == 0) {
  return; // No tiene crédito.
  }
  // Sí tiene.
  (*f)(); // Se ejecuta f().
  *creditos = saldo; // Se actualiza el saldo.
}

El usuario controla la invocación a la función seleccionar_funcion(), a la que puede llamar
todas las veces que desee, intentado ejecutar cualquiera de las opciones disponibles, todas las veces
que quiera.
El código mostrado tiene un problema de seguridad con 2 consecuencias. Determine cuáles son.
Pista: considere los tipos de las variables numéricas involucradas.

** EJERCICIO 17

Asuma que Bob crea un programa para que los usuarios de Linux puedan modificar sus contraseñas
con el siguiente código:

int main (void) {
  cambiarPassword ( );
  return 0;
}

void cambiarPassword() {
  int numeroDeUsuario = obtenerUsuarioActual ( );
  char password[250];
  char passwordConfirmacion[250];
  printf ( " Ingrese su password actual " );
  fgets (password, 250, stdin );
  if (hash(password) == hashDePasswordActual(numeroDeUsuario)) {
      printf ( " Ingrese su nuevo password" );
      fgets (password,250, stdin );
      printf ( "Confirme su nuevo password" );
      gets (passwordConfirmacion );
      i f ( sonIguales (password, passwordConfirmacion)) {
        actualizarPassword(numeroDeUsuario, password );
      }
  }
}

1 y 2) El problema de seguridad en el código se da en la línea "gets (passwordConfirmacion );" donde puede ocurrir un buffer overflow en passwordConfirmacion, ya que tiene una longitud
  acotada de 250 chars pero gets no chequea que el usuario escriba solamente 250 chars, entonces el atacante puede escribir más de 250 caracteres pisando variables locales que están
  direcciones de memoria más altas que passwordConfimacion, como password o numeroDeUsuario, además el atacante podría pisar la dirección de retorno de la función para retornar
  a un código malicioso que puede estar ubicado en otra posición de memoria o haber sido introducido en el mismo buffer por el atacante. En este caso particularmente el atacante
  podría utilizar el buffer overflow para cambiar la contraseña de otro usuario, ya que puede pisar la variable numeroDeUsuario con un valor adecuado de passwordConfirmacion y
  de este modo cambiar la contraseña de otro usuario, por ejemplo el usuario root cuyo número de usuario es 0. 
  Entonces el atacante debería introducir en passwordConfirmation 2 veces la misma contraseña ocupando cada caso 250 bytes, para poder pisar password, y luego debería en los 
  siguientes 4 bytes poner el numero de usuario al cual le quiere cambiar la contraseña, osea debería escribir 504 bytes en el buffer con la forma:
  | contraseñaNueva (250 bytes) | contraseñaNueva (250 bytes) | numeroDeUsuarioAlCualLeQuieroCambiarLaContraseña (4 bytes) | 
  De este modo un atacante podría cammbiar las contraseñas de cualquier usuario.

3) Para que el programa pueda ser ejecutado por cualquier usuario y a la vez tenga los permisos necesarios para cambiar las contraseñas Bob puede poner como owner del ejecutable
   al usuario root, que tiene permisos para escribir el archivo de contraseñas, y activar el flago setuid para que cualquier usuario que corra ese programa tenga los privilegios root.

4) Si Alice podría leer las contraseñas y estas están almacenadas en texto plano entonces puede conocer todas las contraseñas del sistema, en el caso de que estén haseadas
   debería encontrar la función con la que se hasheo y el salt utilizado lo cual dificulta la obtención de las contraseñas originales, pero tampoco lo hace imposible ya que
   Alice podría probar por fuerza bruta muchos hashes con distintos salts hasta encontrar el correcto.
