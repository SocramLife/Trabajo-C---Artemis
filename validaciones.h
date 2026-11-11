#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#define TAM_BUFFER 100   /* maximo de caracteres que se leen por linea */

/* Pide un numero real entre minimo y maximo. Repite hasta que sea valido. */
double leer_double(const char *mensaje, double minimo, double maximo);

/* Pide un numero entero entre minimo y maximo. Repite hasta que sea valido. */
int leer_entero(const char *mensaje, int minimo, int maximo);

/* Pide una respuesta S o N. Devuelve 'S' o 'N'. */
char leer_si_no(const char *mensaje);

/* Muestra un mensaje de error con formato uniforme. */
void mostrar_error(const char *mensaje);

#endif
