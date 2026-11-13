#ifndef ARTEMIS_H
#define ARTEMIS_H

/*constantes del escenario4 (datos del enunciado)*/
#define G             9.80      /* gravedad terrestre (m/s*2)*/
#define MASA_ORION    10400.0   /* masa del modulo de tripulacion (kg)*/
#define V_REINGRESO   11000.0   /* velocidad al entrar (m/s)*/
#define H_REINGRESO   120000.0  /* altura al entrar (m)*/
#define V_PARACAIDAS  25.0      /* velocidad al abrir paracaidas (m/s)*/
#define H_PARACAIDAS  2500.0    /* altura al abrir paracaidas (m)*/
#define V_IMPACTO     8.0       /* velocidad al tocar el agua (m/s)*/
#define HUNDIMIENTO   1.50      /* cuanto se hunde en el agua(m)*/
#define T_FRENADO     400.0     /* duracion del frenado fuerte (m)*/
#define GAMMA_MIN     5.5       /* angulo minimo seguro (grados)*/
#define GAMMA_MAX     7.0       /* angulo maximo seguro (grados)*/

/*registro que representa la capsula*/
typedef struct {
    double masa;       /*kg*/
    double velocidad;  /*m/s*/
    double altura;     /*m*/
    double angulo;     /*grados*/
} Capsula;

/*resultado posible segun el angulo de reingreso*/
typedef enum {
    REBOTE_ATMOSFERICO,       /*angulo menor a gAMMA_MIN*/
    REINGRESO_SEGURO,         /*angulo entre GAMMA_MIN y GAMMA_MAX*/
    DESACELERACION_EXCESIVA   /*angulo mayor a GAMMA_MAX*/
} ResultadoReingreso;

/*energia*/
double energia_cinetica(double masa, double velocidad);   /*k=1/2 m v*2*/
double energia_potencial(double masa, double altura);     /*u =m g h*/
double energia_mecanica(Capsula c);                       /*Em=K + U*/

/*Preguntas del escenario*/
/*a) Trabajo de la fuerza de rozamiento entre dos estados de la capsula (J*/
double trabajo_rozamiento(Capsula inicio, Capsula fin);

/*b) Aceleracion media (m/s^2). Negativa si la capsula frena*/
double desaceleracion_media(double v_inicial, double v_final, double tiempo);

/*b y c) Expresa una aceleracion en multiplos de g*/
double en_unidades_g(double aceleracion);

/*c) Fuerza promedio que ejerce el agua al frenar la capsula (N)*/
double fuerza_impacto(double masa, double v_impacto, double hundimiento);

/*d) Clasifica el angulo de reingreso */
ResultadoReingreso evaluar_angulo(double angulo);

#endif
