#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "utilerias.h"
#include "torneo.h"

const int PRIMERA_OPCION = 1;
inline void intercambiarEquipos(Equipo* primero, Equipo* segundo) {
    Equipo temporal = *primero;
    *primero = *segundo;
    *segundo = temporal;
}

inline void ordenarTabla(const Equipo equipos[], int total, Equipo tabla[]) {
    for (int i = 0; i < total; i++) {
        tabla[i] = equipos[i];
    }
    for (int pasada = 0; pasada < total - 1; pasada++) {
        for (int j = 0; j < total - 1 - pasada; j++) {
            if (tabla[j].puntos < tabla[j + 1].puntos) {
                intercambiarEquipos(&tabla[j], &tabla[j + 1]);
            }
        }
    }
}

inline void imprimirFilaTabla(int posicion, const Equipo& equipo) {
    std::cout << std::left << std::setw(ANCHO_POSICION) << posicion
              << std::setw(ANCHO_NOMBRE) << equipo.nombre
              << std::right << std::setw(ANCHO_ESTADISTICA) << equipo.jugados
              << std::setw(ANCHO_ESTADISTICA) << equipo.ganados
              << std::setw(ANCHO_ESTADISTICA) << equipo.empatados
              << std::setw(ANCHO_ESTADISTICA) << equipo.perdidos
              << std::setw(ANCHO_ESTADISTICA) << equipo.golesFavor
              << std::setw(ANCHO_ESTADISTICA) << equipo.golesContra
              << std::setw(ANCHO_PUNTOS) << equipo.puntos << "\n";
}

inline void mostrarTabla(const Equipo equipos[], int total, bool simulado) {
    if (!reporteDisponible(simulado)) {
        return;
    }

    Equipo tabla[MAX_EQUIPOS];
    ordenarTabla(equipos, total, tabla);

    imprimirTitulo("TABLA DE POSICIONES");
    std::cout << std::left << std::setw(ANCHO_POSICION) << "POS"
              << std::setw(ANCHO_NOMBRE) << "EQUIPO"
              << std::right << std::setw(ANCHO_ESTADISTICA) << "PJ"
              << std::setw(ANCHO_ESTADISTICA) << "PG"
              << std::setw(ANCHO_ESTADISTICA) << "PE"
              << std::setw(ANCHO_ESTADISTICA) << "PP"
              << std::setw(ANCHO_ESTADISTICA) << "GF"
              << std::setw(ANCHO_ESTADISTICA) << "GC"
              << std::setw(ANCHO_PUNTOS) << "PTS" << "\n";
    for (int i = 0; i < total; i++) {
        imprimirFilaTabla(i + 1, tabla[i]);
    }
}

inline int buscarLideres(const Equipo tabla[], int total, const Equipo* lideres[]) {
    int cantidad = 0;
    int puntosLider = tabla[0].puntos;
    for (int i = 0; i < total && tabla[i].puntos == puntosLider; i++) {
        lideres[cantidad] = &tabla[i];
        cantidad++;
    }
    return cantidad;
}

inline const Equipo* elegirCampeon(const Equipo* lideres[], int cantidad) {
    std::cout << "Hay un empate en el primer lugar con "
              << lideres[0]->puntos << " puntos.\n";
    for (int i = 0; i < cantidad; i++) {
        std::cout << (i + PRIMERA_OPCION) << ". " << lideres[i]->nombre << "\n";
    }

    int opcion = leerEntero("Elige al campeon: ");
    while (opcion < PRIMERA_OPCION || opcion >= cantidad + PRIMERA_OPCION) {
        std::cout << "Opcion no valida. Elige un numero del " << PRIMERA_OPCION
                  << " al " << cantidad << ".\n";
        opcion = leerEntero("Elige al campeon: ");
    }
    return lideres[opcion - PRIMERA_OPCION];
}

inline void mostrarCampeon(const Equipo equipos[], int total, bool simulado) {
    if (!reporteDisponible(simulado)) {
        return;
    }

    Equipo tabla[MAX_EQUIPOS];
    ordenarTabla(equipos, total, tabla);
    const Equipo* lideres[MAX_EQUIPOS];
    int cantidad = buscarLideres(tabla, total, lideres);

    imprimirTitulo("CAMPEON DEL TORNEO");
    const Equipo* campeon = lideres[0];
    if (cantidad > 1) {
        campeon = elegirCampeon(lideres, cantidad);
        std::cout << "\n";
    }
    std::cout << "Campeon: " << campeon->nombre << "\n";
    std::cout << "Puntos: " << campeon->puntos << "\n";
}