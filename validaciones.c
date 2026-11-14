#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "validaciones.h"

/* Funciones auxiliares (privadas del modulo) */

/* Lee una linea completa del teclado y le quita el '\n' final
   Devuelve 1 si la linea entro completa en el buffer, 0 si era demasiado larga
   Si se cierra la entrada (ctrl+d/ ctrl+z), termina el programa. */
static int leer_linea(char *buffer, int tam)
{
    int c;

    if (fgets(buffer, tam, stdin) == NULL) {
        printf("\nEntrada finalizada. Saliendo del programa.\n");
        exit(EXIT_FAILURE);
    }

    if (strchr(buffer, '\n') == NULL) {
        /* La linea no entro completa: se descarta el resto que quedo pendiente */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

/* reemplaza las comas por puntos, para aceptar "6,5" ademas de 6.5" */
static void comas_a_puntos(char *texto)
{
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
}

/* indica si a partir de 'p' solo quedan espacios hasta el final del texto*/
static int solo_espacios(const char *p)
{
    while (isspace((unsigned char)*p)) {
        p++;
    }
    return *p == '\0';
}

/* convierte texto a double, devuelve 1 si el texto es un numero valido y deja el valor en *resultado; devuelve 0 si no lo es. */
static int convertir_double(const char *texto, double *resultado)
{
    char *fin;
    double valor;

    errno = 0;
    valor = strtod(texto, &fin);

    if (fin == texto)        return 0;   /* no habia ningun numero: "abc" o vacio */
    if (!solo_espacios(fin)) return 0;   /* sobro texto: "12abc"                   */
    if (errno == ERANGE)     return 0;   /* numero demasiado grande: "1e999"       */

    *resultado = valor;
    return 1;
}

/* igual que convertir_double pero para enteros */
static int convertir_entero(const char *texto, long *resultado)
{
    char *fin;
    long valor;

    errno = 0;
    valor = strtol(texto, &fin, 10);

    if (fin == texto)        return 0;
    if (!solo_espacios(fin)) return 0;   /* rechaza tambien "3.5" */
    if (errno == ERANGE)     return 0;

    *resultado = valor;
    return 1;
}

/* funciones publicas (declaradas en validaciones,h)*/

void mostrar_error(const char *mensaje)
{
    printf("  [ERROR] %s\n", mensaje);
}

void esperar_enter(void)
{
    char buffer[TAM_BUFFER];

    printf("\nPresione Enter para volver al menu...");
    leer_linea(buffer, TAM_BUFFER);   /* lo escrito se descarta */
}

void limpiar_pantalla(void)
{
    /* Secuencias ANSI: \033[2J borra la pantalla, \033[H lleva el cursor al inicio */
    printf("\033[2J\033[H");
    fflush(stdout);
}


double leer_double(const char *mensaje, double minimo, double maximo)
{
    char buffer[TAM_BUFFER];
    double valor = 0.0;
    int valido = 0;

    do {
        printf("%s [%.2f a %.2f]: ", mensaje, minimo, maximo);

        if (!leer_linea(buffer, TAM_BUFFER)) {
            mostrar_error("La entrada es demasiado larga.");
        } else {
            comas_a_puntos(buffer);
            if (!convertir_double(buffer, &valor)) {
                mostrar_error("Debe ingresar un numero.");
            } else if (!(valor >= minimo && valor <= maximo)) {
                mostrar_error("El valor esta fuera del rango permitido.");
            } else {
                valido = 1;
            }
        }
    } while (!valido);

    return valor;
}

int leer_entero(const char *mensaje, int minimo, int maximo)
{
    char buffer[TAM_BUFFER];
    long valor = 0;
    int valido = 0;

    do {
        printf("%s [%d a %d]: ", mensaje, minimo, maximo);

        if (!leer_linea(buffer, TAM_BUFFER)) {
            mostrar_error("La entrada es demasiado larga.");
        } else if (!convertir_entero(buffer, &valor)) {
            mostrar_error("Debe ingresar un numero entero.");
        } else if (valor < minimo || valor > maximo) {
            mostrar_error("El valor esta fuera del rango permitido.");
        } else {
            valido = 1;
        }
    } while (!valido);

    return (int)valor;
}

char leer_si_no(const char *mensaje)
{
    char buffer[TAM_BUFFER];
    char respuesta = ' ';
    int valido = 0;

    do {
        printf("%s (S/N): ", mensaje);

        if (!leer_linea(buffer, TAM_BUFFER)) {
            mostrar_error("La entrada es demasiado larga.");
        } else if (strlen(buffer) != 1) {
            mostrar_error("Ingrese una sola letra: S o N.");
        } else {
            respuesta = (char)toupper((unsigned char)buffer[0]);
            if (respuesta == 'S' || respuesta == 'N') {
                valido = 1;
            } else {
                mostrar_error("Ingrese S o N.");
            }
        }
    } while (!valido);

    return respuesta;
}
