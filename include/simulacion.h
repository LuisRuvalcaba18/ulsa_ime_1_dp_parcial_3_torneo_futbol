#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "utilerias.h"
#include "torneo.h"
#include "escenario_prueba.h"

// Modos de simulacion que se ofrecen al usuario
const int MODO_ALEATORIO = 1;
const int MODO_PRUEBA = 2;

// Columnas de la tabla GOLES_PRUEBA
const int COLUMNA_GOLES_LOCAL = 0;
const int COLUMNA_GOLES_VISITANTE = 1;

// Pregunta el modo de simulacion y lo vuelve a pedir si no existe
// Devuelve a MODO_ALEATORIO o MODO_PRUEBA.
inline int leerModoSimulacion() {
    std::cout << MODO_ALEATORIO << ". Modo aleatorio\n";
    std::cout << MODO_PRUEBA << ". Modo de prueba\n";
    int modo = leerEntero("Elige el modo: ");
    while (modo != MODO_ALEATORIO && modo != MODO_PRUEBA) {
        std::cout << "Modo no valido. Escribe " << MODO_ALEATORIO
                  << " o " << MODO_PRUEBA << ".\n";
        modo = leerEntero("Elige el modo: ");
    }
    return modo;
}

// Genera los partidos con dos ciclos anidados el equipo 'local'
// juega contra cada equipo registrado despues de el.
// Recibe el arreglo de partidos (se llena), cuantos equipos hay y el modo
// Devuelve cuantos partidos se generaron
inline int generarPartidos(Partido partidos[], int totalEquipos, int modo) {
    int numero = 0;
    for (int local = 0; local < totalEquipos; local++) {
        for (int visitante = local + 1; visitante < totalEquipos; visitante++) {
            Partido partido;
            partido.local = local;
            partido.visitante = visitante;
            if (modo == MODO_PRUEBA) {
                partido.golesLocal = GOLES_PRUEBA[numero][COLUMNA_GOLES_LOCAL];
                partido.golesVisitante = GOLES_PRUEBA[numero][COLUMNA_GOLES_VISITANTE];
            } else {
                partido.golesLocal = numeroAleatorio();
                partido.golesVisitante = numeroAleatorio();
            }
            partidos[numero] = partido;
            numero++;
        }
    }
    return numero;
}

// Simula el torneo solo una vez y solo con MAX_EQUIPOS equipos
// Recibe el arreglo de partidos (se llena), totalPartidos y simulado
//         POR REFERENCIA se actualizan y cuantos equipos hay
// Devuelve true si se simulo, false si se rechazo.
inline bool simularTorneo(Partido partidos[], int& totalPartidos,
                          int totalEquipos, bool& simulado) {
    if (simulado) {
        std::cout << "Rechazado: el torneo ya se simulo. "
                  << "Solo se simula una vez por ejecucion.\n";
        return false;
    }
    if (totalEquipos < MAX_EQUIPOS) {
        std::cout << "Rechazado: se necesitan " << MAX_EQUIPOS
                  << " equipos para simular y hay " << totalEquipos << ".\n";
        return false;
    }

    int modo = leerModoSimulacion();
    totalPartidos = generarPartidos(partidos, totalEquipos, modo);
    simulado = true;
    std::cout << "Torneo simulado: se jugaron " << totalPartidos << " partidos.\n";
    return true;
}

// Imprime un renglon del reporte de resultados
// Recibe el numero de partido, el partido como const& y los equipos
//         como const, porque solo se leen.
inline void imprimirPartido(int numero, const Partido& partido,
                            const Equipo equipos[]) {
    std::cout << std::left << std::setw(ANCHO_NUMERO) << numero
              << std::setw(ANCHO_NOMBRE) << equipos[partido.local].nombre
              << std::setw(ANCHO_MARCADOR)
              << textoMarcador(partido.golesLocal, partido.golesVisitante)
              << equipos[partido.visitante].nombre << "\n";
}

// Muestra los resultados de todos los partidos, en el orden en que se jugaron
// Recibe: los arreglos como const solo se leen y si ya se simulo
inline void mostrarResultados(const Equipo equipos[], const Partido partidos[],
                              int totalPartidos, bool simulado) {
    if (!reporteDisponible(simulado)) {
        return;
    }

    imprimirTitulo("RESULTADOS DE LOS PARTIDOS");
    std::cout << std::left << std::setw(ANCHO_NUMERO) << "#"
              << std::setw(ANCHO_NOMBRE) << "LOCAL"
              << std::setw(ANCHO_MARCADOR) << "MARCADOR"
              << "VISITANTE" << "\n";
    for (int i = 0; i < totalPartidos; i++) {
        imprimirPartido(i + 1, partidos[i], equipos);
    }
}
