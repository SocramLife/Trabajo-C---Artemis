#ifndef JUEGO_H
#define JUEGO_H

#include "artemis.h"

#define MAX_MISIONES 10   // cantidad maxima de misiones por partida 

// - Reglas del juego - 
//  Son simplificaciones propias del juego, no datos del enunciado. 

#define GAMMA_IDEAL        6.25   // centro de la ventana segura (grados)            
#define H_PARACAIDAS_MIN   1.5    // km: por debajo, los paracaidas abren tarde       
#define H_PARACAIDAS_IDEAL 2.5    // km: altura de apertura del enunciado             
#define H_PARACAIDAS_MAX   3.5    // km: por encima, el viento desvia la capsula      
#define V_IMPACTO_TARDIO   15.0   // m/s al tocar el agua si abren tarde              
#define LIMITE_IMPACTO     5.0    // veces su peso que soporta la estructura          

// - Registro de una mision jugada - 
typedef struct {
    int numero;
    double angulo;               // grados                           
    double altura_paracaidas;    // m (0 si no se llego a esa fase)  
    double g_frenado;            // desaceleracion en multiplos de g 
    double trabajo;              // J                                
    double impacto_en_pesos;     // fuerza del agua / peso           
    ResultadoReingreso reingreso;
    int exitosa;                 // 1 = si, 0 = no                   
    int puntaje;                 // 0 a 100                          
} RegistroMision;

void mostrar_reglas(void);
void jugar_mision(RegistroMision *registro, int numero);
void modo_analisis(void);
void mostrar_reporte(const RegistroMision historial[], int cantidad);

#endif
