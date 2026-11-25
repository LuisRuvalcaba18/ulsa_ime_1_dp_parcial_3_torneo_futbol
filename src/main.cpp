#include <iostream>

#include "utilerias.h"
#include "torneo.h"
#include "registro_equipos.h"  
#include "simulacion.h"         
#include "TablaPosiciones.h"    
#include "Matriz.h"             
#include "clasificación.h"      
#include "Consultar.h"    

// Opciones del menu.
const int OPCION_REGISTRAR = 1;
const int OPCION_MOSTRAR_EQUIPOS = 2;
const int OPCION_SIMULAR = 3;
const int OPCION_RESULTADOS = 4;
const int OPCION_TABLA = 5;
const int OPCION_CAMPEON = 6;
const int OPCION_CONSULTAR = 7;
const int OPCION_MATRIZ = 8;
const int OPCION_SALIR = 9;

// Imprime el menu principal.
void mostrarMenu() {
    std::cout << "\n===== TORNEO DE FUTBOL =====\n";
    std::cout << OPCION_REGISTRAR << ". Registrar equipo\n";
    std::cout << OPCION_MOSTRAR_EQUIPOS << ". Mostrar equipos\n";
    std::cout << OPCION_SIMULAR << ". Simular torneo\n";
    std::cout << OPCION_RESULTADOS << ". Mostrar resultados\n";
    std::cout << OPCION_TABLA << ". Mostrar tabla de posiciones\n";
    std::cout << OPCION_CAMPEON << ". Mostrar campeon\n";
    std::cout << OPCION_CONSULTAR << ". Consultar equipo\n";
    std::cout << OPCION_MATRIZ << ". Mostrar matriz de enfrentamientos\n";
    std::cout << OPCION_SALIR << ". Salir\n";
}      

// Ejecuta la opcion elegida del menu
// Recibe la opcion, los arreglos como APUNTADOR a su primer elemento
//         equipos, partidos y la matriz goles, y la DIRECCION de
//         totalEquipos, totalPartidos y torneoSimulado, para leerlos
//         y modificarlos con el operador 
void ejecutarOpcion(int opcion, Equipo* equipos, int* totalEquipos,
                    Partido* partidos, int* totalPartidos,
                    int goles[][MAX_EQUIPOS], bool* torneoSimulado) {
    switch (opcion) {
        case OPCION_REGISTRAR:
            registrarEquipo(equipos, *totalEquipos);
            break;
        case OPCION_MOSTRAR_EQUIPOS:
            mostrarEquipos(equipos, *totalEquipos);
            break;
        case OPCION_SIMULAR:
            if (simularTorneo(partidos, *totalPartidos, *totalEquipos, *torneoSimulado)) {
            
            }
            break;
        case OPCION_RESULTADOS:
            mostrarResultados(equipos, partidos, *totalPartidos, *torneoSimulado);
            break;
    }
}