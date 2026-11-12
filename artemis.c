#include "artemis.h"

/* Energia */

double energia_cinetica(double masa, double velocidad)
{
    return 0.5 * masa * velocidad * velocidad;
}

double energia_potencial(double masa, double altura)
{
    return masa * G * altura;
}

double energia_mecanica(Capsula c)
{
    return energia_cinetica(c.masa, c.velocidad) + energia_potencial(c.masa, c.altura);
}

/* Preguntas del escenario */

/* a) El trabajo del rozamiento es la energia mecanica que se perdio:
      W = Em final - Em inicial (da negativo porque la energia disminuye) */
double trabajo_rozamiento(Capsula inicio, Capsula fin)
{
    return energia_mecanica(fin) - energia_mecanica(inicio);
}

/* b) a = (v final - v inicial) / tiempo
      El tiempo debe ser mayor a 0: se garantiza al validar la entrada. */
double desaceleracion_media(double v_inicial, double v_final, double tiempo)
{
    return (v_final - v_inicial) / tiempo;
}

double en_unidades_g(double aceleracion)
{
    return aceleracion / G;
}

/* c) El agua debe sostener el peso (m g) y ademas de quitar toda la energia
      cinetica en la distancia que se hunde: F = m g + K / d
      El hundimiento debe ser mayor a 0: se garantiza al validar la entrada. */
double fuerza_impacto(double masa, double v_impacto, double hundimiento)
{
    return masa * G + energia_cinetica(masa, v_impacto) / hundimiento;
}

/* d) Compara al angulo con la ventana de seguridad */
ResultadoReingreso evaluar_angulo(double angulo)
{
    ResultadoReingreso resultado;

    if (angulo < GAMMA_MIN) {
        resultado = REBOTE_ATMOSFERICO;
    } else if (angulo > GAMMA_MAX) {
        resultado = DESACELERACION_EXCESIVA;
    } else {
        resultado = REINGRESO_SEGURO;
    }

    return resultado;
}
