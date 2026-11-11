#ifndef ARTEMIS_H
#define ARTEMIS_H

/* - Constantes (datos del enunciado) - */
#define G             9.80      /* gravedad terrestre (m/s^2)          */
#define MASA_ORION    10400.0   /* masa del modulo de tripulación (kg) */
#define V_REINGRESO   11000.0   /* velocidad al entrar (m/s)           */
#define H_REINGRESO   120000.0  /* altura al entrar (m)                */
#define V_PARACAIDAS  25.0      /* velocidad al abrir paracaidas (m/s) */
#define H_PARACAIDAS  2500.0    /* altura al abrir paracaidas (m)      */
#define V_IMPACTO     8.0       /* velocidad al tocar el agua (m/s)    */
#define HUNDIMIENTO   1.50      /* cuanto se hunde en el agua (m)      */
#define T_FRENADO     400.0     /* duracion del frenado fuerte (s)     */
#define GAMMA_MIN     5.5       /* angulo minimo seguro (grados)       */
#define GAMMA_MAX     7.0       /* angulo maximo seguro (grados)       */

/* - Registro que representa la capsula - */
typedef struct {
    double masa;       /* kg      */
    double velocidad;  /* m/s     */
    double altura;     /* m       */
    double angulo;     /* grados  */
} Capsula;

#endif
