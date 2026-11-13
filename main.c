#include <stdio.h>
#include "juego.h"
#include "validaciones.h"

static void mostrar_menu(void)
{
    printf("\n==========================================\n");
    printf("   SIMULADOR ARTEMIS - REINGRESO ORION\n");
    printf("==========================================\n");
    printf("1. Jugar una mision\n");
    printf("2. Modo analisis (calculos con datos propios)\n");
    printf("3. Ver reporte de desempeno\n");
    printf("4. Ver reglas\n");
    printf("5. Salir\n");
}

int main(void)
{
    RegistroMision historial[MAX_MISIONES];
    int cantidad = 0;
    int opcion;

    do {
        mostrar_menu();
        opcion = leer_entero("Elija una opcion", 1, 5);

        switch (opcion) {
            case 1:
                if (cantidad < MAX_MISIONES) {
                    jugar_mision(&historial[cantidad], cantidad + 1);
                    cantidad++;
                } else {
                    mostrar_error("se alcanzo el maximo de misiones de la partida");
                }
                break;
            case 2:
                modo_analisis();
                break;
            case 3:
                mostrar_reporte(historial, cantidad);
                break;
            case 4:
                mostrar_reglas();
                break;
            case 5:
                mostrar_reporte(historial, cantidad);
                printf("\nfin de la simulacion\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
