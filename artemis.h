#ifndef ARTEMIS_H
#define ARTEMIS_H

/* - Constantes (datos del enunciado) - */
#define G             9.80      /* gravedad terrestre (m/s^2)          */
#define MASA_ORION    10400.0   /* masa del módulo de tripulación (kg) */
#define V_REINGRESO   11000.0   /* velocidad al entrar (m/s)           */
#define H_REINGRESO   120000.0  /* altura al entrar (m)                */
#define V_PARACAIDAS  25.0      /* velocidad al abrir paracaídas (m/s) */
#define H_PARACAIDAS  2500.0    /* altura al abrir paracaídas (m)      */
#define V_IMPACTO     8.0       /* velocidad al tocar el agua (m/s)    */
#define HUNDIMIENTO   1.50      /* cuánto se hunde en el agua (m)      */
#define T_FRENADO     400.0     /* duración del frenado fuerte (s)     */
#define GAMMA_MIN     5.5       /* ángulo mínimo seguro (grados)       */
#define GAMMA_MAX     7.0       /* ángulo máximo seguro (grados)       */

/* - Registro que representa la cápsula - */
typedef struct {
    double masa;       /* kg      */
    double velocidad;  /* m/s     */
    double altura;     /* m       */
    double angulo;     /* grados  */
} Capsula;

#endif
