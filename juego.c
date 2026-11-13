#include <stdio.h>
#include <math.h>
#include "juego.h"
#include "validaciones.h"

/*  Funciones auxiliares (privadas de este modulo) */

/* Regla del juego: cuanto mas empinado el angulo, mas corto y brusco
   es el frenado. Con el angulo ideal dura T_FRENADO (400 s). */
static double duracion_frenado(double angulo)
{
    return T_FRENADO * GAMMA_IDEAL / angulo;
}

/* Puntaje de 0 a 100: hasta 50 por precision del angulo
   y hasta 50 por la altura de apertura de los paracaidas. */
static int calcular_puntaje(double angulo, double altura_km)
{
    double puntos_angulo;
    double puntos_paracaidas;
    double margen_angulo = GAMMA_MAX - GAMMA_IDEAL;

    puntos_angulo = 50.0 * (1.0 - fabs(angulo - GAMMA_IDEAL) / margen_angulo);

    if (altura_km > H_PARACAIDAS_MAX) {
        puntos_paracaidas = 10.0;
    } else {
        puntos_paracaidas = 50.0 * (1.0 - fabs(altura_km - H_PARACAIDAS_IDEAL)
                                          / (H_PARACAIDAS_IDEAL - H_PARACAIDAS_MIN));
    }

    return (int)(puntos_angulo + puntos_paracaidas + 0.5);
}

/* Devuelve un texto que describe el resultado del reingreso. */
static const char *nombre_reingreso(ResultadoReingreso r)
{
    const char *texto;

    switch (r) {
        case REBOTE_ATMOSFERICO:
            texto = "Rebote";
            break;
        case DESACELERACION_EXCESIVA:
            texto = "Exceso g";
            break;
        default:
            texto = "Seguro";
            break;
    }

    return texto;
}

/* Funciones publicas (declaradas en juego.h) */

void mostrar_reglas(void)
{
    printf("\n===== REGLAS DEL JUEGO =====\n");
    printf("Sos el comandante de la capsula Orion (%.0f kg), que vuelve de la Luna.\n", MASA_ORION);
    printf("Entra a la atmosfera a %.0f m/s y %.0f km de altura.\n", V_REINGRESO, H_REINGRESO / 1000.0);
    printf("\nFASE 1 - Reingreso: elegis el angulo de entrada.\n");
    printf("  - Menor a %.1f grados: la capsula rebota en la atmosfera y se pierde.\n", GAMMA_MIN);
    printf("  - Mayor a %.1f grados: la desaceleracion es excesiva para la tripulacion.\n", GAMMA_MAX);
    printf("  - Entre %.1f y %.1f: reingreso seguro. Cuanto mas cerca de %.2f, mas puntos.\n",
           GAMMA_MIN, GAMMA_MAX, GAMMA_IDEAL);
    printf("FASE 2 - Frenado: el escudo termico frena la capsula hasta %.0f m/s.\n", V_PARACAIDAS);
    printf("FASE 3 - Paracaidas: elegis a que altura abrirlos.\n");
    printf("  - Por debajo de %.1f km abren tarde y el impacto es peligroso.\n", H_PARACAIDAS_MIN);
    printf("  - Por encima de %.1f km el viento te aleja del buque de rescate.\n", H_PARACAIDAS_MAX);
    printf("  - La altura ideal es %.1f km.\n", H_PARACAIDAS_IDEAL);
    printf("FASE 4 - Amerizaje: la estructura soporta hasta %.1f veces su peso.\n", LIMITE_IMPACTO);
    printf("\nPuntaje maximo por mision: 100 puntos.\n");
}

void jugar_mision(RegistroMision *registro, int numero)
{
    Capsula inicio;
    Capsula fin;
    double tiempo;
    double aceleracion;
    double altura_km;
    double v_impacto;
    double fuerza;

    /* Valores iniciales del registro, por si la mision termina antes */
    registro->numero = numero;
    registro->altura_paracaidas = 0.0;
    registro->g_frenado = 0.0;
    registro->trabajo = 0.0;
    registro->impacto_en_pesos = 0.0;
    registro->exitosa = 0;
    registro->puntaje = 0;

    printf("\n========== MISION %d ==========\n", numero);

    /* ----- FASE 1: angulo de reingreso ----- */
    printf("\nFASE 1 - REINGRESO\n");
    printf("La capsula llega a %.0f km de altura a %.0f m/s.\n", H_REINGRESO / 1000.0, V_REINGRESO);
    registro->angulo = leer_double("Angulo de reingreso (grados)", 0.0, 90.0);
    registro->reingreso = evaluar_angulo(registro->angulo);

    if (registro->reingreso == REBOTE_ATMOSFERICO) {
        printf("\n>> El angulo es demasiado plano: la capsula rebota en la atmosfera\n");
        printf(">> y sale despedida al espacio. MISION FALLIDA.\n");
        return;
    }

    tiempo = duracion_frenado(registro->angulo);
    aceleracion = desaceleracion_media(V_REINGRESO, V_PARACAIDAS, tiempo);
    registro->g_frenado = fabs(en_unidades_g(aceleracion));

    if (registro->reingreso == DESACELERACION_EXCESIVA) {
        printf("\n>> El angulo es demasiado empinado: el frenado dura solo %.0f s\n", tiempo);
        printf(">> y la tripulacion soporta %.2f g. MISION FALLIDA.\n", registro->g_frenado);
        return;
    }

    /* ----- FASE 2: frenado aerodinamico ----- */
    printf("\nFASE 2 - FRENADO AERODINAMICO\n");
    printf("Reingreso seguro. El escudo termico frena la capsula durante %.0f s.\n", tiempo);
    printf("Desaceleracion media: %.2f m/s^2 (%.2f g).\n", fabs(aceleracion), registro->g_frenado);

    /* ----- FASE 3: apertura de paracaidas ----- */
    printf("\nFASE 3 - PARACAIDAS\n");
    printf("La capsula baja a %.0f m/s.\n", V_PARACAIDAS);
    altura_km = leer_double("Altura de apertura de paracaidas (km)", 0.5, 6.0);
    registro->altura_paracaidas = altura_km * 1000.0;

    inicio.masa = MASA_ORION;
    inicio.velocidad = V_REINGRESO;
    inicio.altura = H_REINGRESO;
    inicio.angulo = registro->angulo;

    fin.masa = MASA_ORION;
    fin.velocidad = V_PARACAIDAS;
    fin.altura = registro->altura_paracaidas;
    fin.angulo = registro->angulo;

    registro->trabajo = trabajo_rozamiento(inicio, fin);
    printf("Energia disipada por el escudo termico: %.3e J\n", -registro->trabajo);

    if (altura_km < H_PARACAIDAS_MIN) {
        v_impacto = V_IMPACTO_TARDIO;
        printf(">> Los paracaidas abren demasiado tarde y no frenan del todo.\n");
    } else if (altura_km > H_PARACAIDAS_MAX) {
        v_impacto = V_IMPACTO;
        printf(">> Apertura temprana: el viento aleja la capsula del buque de rescate.\n");
    } else {
        v_impacto = V_IMPACTO;
        printf(">> Apertura correcta de los paracaidas.\n");
    }

    /* ----- FASE 4: amerizaje ----- */
    printf("\nFASE 4 - AMERIZAJE\n");
    fuerza = fuerza_impacto(MASA_ORION, v_impacto, HUNDIMIENTO);
    registro->impacto_en_pesos = fuerza / (MASA_ORION * G);
    printf("La capsula toca el agua a %.1f m/s.\n", v_impacto);
    printf("Fuerza del agua: %.0f N (%.2f veces su peso).\n", fuerza, registro->impacto_en_pesos);

    if (registro->impacto_en_pesos > LIMITE_IMPACTO) {
        printf("\n>> El impacto supera lo que soporta la estructura. MISION FALLIDA.\n");
    } else {
        registro->exitosa = 1;
        registro->puntaje = calcular_puntaje(registro->angulo, altura_km);
        printf("\n>> Amerizaje exitoso en el Oceano Pacifico. MISION CUMPLIDA.\n");
        printf(">> Puntaje: %d / 100\n", registro->puntaje);
    }
}

void modo_analisis(void)
{
    Capsula inicio;
    Capsula fin;
    double tiempo;
    double aceleracion;
    double v_impacto;
    double hundimiento;
    double fuerza;
    double angulo;
    ResultadoReingreso resultado;

    printf("\n===== MODO ANALISIS =====\n");
    printf("Ingrese los datos del reingreso (valores del enunciado entre parentesis).\n\n");

    inicio.masa = leer_double("Masa de la capsula en kg (10400)", 1000.0, 50000.0);
    inicio.velocidad = leer_double("Velocidad de reingreso en m/s (11000)", 1000.0, 15000.0);
    inicio.altura = leer_double("Altura de reingreso en km (120)", 50.0, 200.0) * 1000.0;
    inicio.angulo = 0.0;

    fin.masa = inicio.masa;
    fin.velocidad = leer_double("Velocidad al abrir paracaidas en m/s (25)", 1.0, 500.0);
    fin.altura = leer_double("Altura de apertura de paracaidas en km (2.5)", 0.5, 10.0) * 1000.0;
    fin.angulo = 0.0;

    tiempo = leer_double("Duracion del frenado en s (400)", 1.0, 2000.0);
    v_impacto = leer_double("Velocidad de impacto en el agua en m/s (8)", 0.1, 50.0);
    hundimiento = leer_double("Distancia que se hunde en el agua en m (1.5)", 0.1, 10.0);
    angulo = leer_double("Angulo de reingreso en grados (6)", 0.0, 90.0);

    printf("\n----- RESULTADOS -----\n");

    printf("a) Trabajo del rozamiento atmosferico: %.4e J\n",
           trabajo_rozamiento(inicio, fin));

    aceleracion = desaceleracion_media(inicio.velocidad, fin.velocidad, tiempo);
    printf("b) Desaceleracion media: %.2f m/s^2 = %.2f g\n",
           fabs(aceleracion), fabs(en_unidades_g(aceleracion)));

    fuerza = fuerza_impacto(inicio.masa, v_impacto, hundimiento);
    printf("c) Fuerza promedio del agua: %.0f N = %.2f veces el peso\n",
           fuerza, fuerza / (inicio.masa * G));

    resultado = evaluar_angulo(angulo);
    printf("d) Angulo de %.2f grados: ", angulo);
    if (resultado == REBOTE_ATMOSFERICO) {
        printf("menor a %.1f. La capsula rebota en la atmosfera y sale al espacio.\n", GAMMA_MIN);
    } else if (resultado == DESACELERACION_EXCESIVA) {
        printf("mayor a %.1f. La desaceleracion es excesiva y pone en riesgo a la tripulacion.\n", GAMMA_MAX);
    } else {
        printf("dentro de la ventana de seguridad. Reingreso seguro.\n");
    }
}

void mostrar_reporte(const RegistroMision historial[], int cantidad)
{
    int i;
    int exitosas = 0;
    int suma_puntaje = 0;
    int mejor = -1;

    printf("\n========== REPORTE DE DESEMPENO ==========\n");

    if (cantidad == 0) {
        printf("Todavia no se jugo ninguna mision.\n");
        return;
    }

    printf("%-4s %-8s %-11s %-8s %-10s %-10s %-8s\n",
           "N", "Angulo", "Paracaidas", "Frenado", "Impacto", "Reingreso", "Puntaje");

    for (i = 0; i < cantidad; i++) {
        printf("%-4d %-8.2f ", historial[i].numero, historial[i].angulo);

        if (historial[i].altura_paracaidas > 0.0) {
            printf("%-11.2f ", historial[i].altura_paracaidas / 1000.0);
            printf("%-8.2f %-10.2f ", historial[i].g_frenado, historial[i].impacto_en_pesos);
        } else {
            printf("%-11s %-8s %-10s ", "-", "-", "-");
        }

        printf("%-10s %d\n", nombre_reingreso(historial[i].reingreso), historial[i].puntaje);

        if (historial[i].exitosa) {
            exitosas++;
            suma_puntaje += historial[i].puntaje;
            if (mejor == -1 || historial[i].puntaje > historial[mejor].puntaje) {
                mejor = i;
            }
        }
    }

    printf("\n(Paracaidas en km, Frenado en g, Impacto en veces el peso)\n");
    printf("Misiones exitosas: %d de %d\n", exitosas, cantidad);

    if (exitosas > 0) {
        printf("Puntaje promedio de las exitosas: %.1f\n", (double)suma_puntaje / exitosas);
        printf("Mejor mision: N %d con %d puntos\n",
               historial[mejor].numero, historial[mejor].puntaje);
    }
}
