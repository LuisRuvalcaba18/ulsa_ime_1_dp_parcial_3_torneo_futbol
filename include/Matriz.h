#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "torneo.h"

// Texto de la diagonal: un equipo no juega contra si mismo.
const std::string CELDA_DIAGONAL = "---";

// Separador cuando hay varios equipos empatados.
const std::string SEPARADOR_NOMBRES = ", ";

// Llena la matriz: goles[fila][columna] son los goles que el equipo
// 'fila' le anoto al equipo 'columna'.
// Recibe: los partidos como const y la matriz, que se llena.
inline void llenarMatriz(const Partido partidos[], int totalPartidos,
                         int goles[][MAX_EQUIPOS]) {
    for (int fila = 0; fila < MAX_EQUIPOS; fila++) {
        for (int columna = 0; columna < MAX_EQUIPOS; columna++) {
            goles[fila][columna] = 0;
        }
    }
    for (int i = 0; i < totalPartidos; i++) {
        const Partido& partido = partidos[i];
        goles[partido.local][partido.visitante] = partido.golesLocal;
        goles[partido.visitante][partido.local] = partido.golesVisitante;
    }
}

// Suma la fila de un equipo: son sus goles a favor.
inline int sumarFila(const int goles[][MAX_EQUIPOS], int total, int fila) {
    int suma = 0;
    for (int columna = 0; columna < total; columna++) {
        if (columna != fila) {
            suma += goles[fila][columna];
        }
    }
    return suma;
}

// Suma la columna de un equipo: son sus goles en contra.
inline int sumarColumna(const int goles[][MAX_EQUIPOS], int total, int columna) {
    int suma = 0;
    for (int fila = 0; fila < total; fila++) {
        if (fila != columna) {
            suma += goles[fila][columna];
        }
    }
    return suma;
}

// Arma el texto de una celda: primero los goles del equipo de la fila.
inline std::string textoCelda(const int goles[][MAX_EQUIPOS], int fila, int columna) {
    if (fila == columna) {
        return CELDA_DIAGONAL;
    }
    return std::to_string(goles[fila][columna]) + "-"
           + std::to_string(goles[columna][fila]);
}

// Imprime la matriz recorriendola por filas y columnas.
inline void imprimirMatriz(const Equipo equipos[], int total,
                           const int goles[][MAX_EQUIPOS]) {
    std::cout << std::left << std::setw(ANCHO_NOMBRE) << "";
    for (int columna = 0; columna < total; columna++) {
        std::cout << std::right << std::setw(ANCHO_CELDA) << equipos[columna].abreviatura;
    }
    std::cout << "\n";

    for (int fila = 0; fila < total; fila++) {
        std::cout << std::left << std::setw(ANCHO_NOMBRE) << equipos[fila].nombre;
        for (int columna = 0; columna < total; columna++) {
            std::cout << std::right << std::setw(ANCHO_CELDA)
                      << textoCelda(goles, fila, columna);
        }
        std::cout << "\n";
    }
}

// Muestra el mejor valor el mayor o el menor y a todos los equipos
// que lo tienen, en orden de registro.
// Recibe: los equipos, sus valores, si se busca el mayor, la etiqueta
//         "Mejor ataque" y la descripcion "goles a favor"
inline void mostrarMejores(const Equipo equipos[], int total, const int valores[],
                           bool buscarMayor, const std::string& etiqueta,
                           const std::string& descripcion) {
    int mejor = valores[0];
    for (int i = 1; i < total; i++) {
        if ((buscarMayor && valores[i] > mejor) || (!buscarMayor && valores[i] < mejor)) {
            mejor = valores[i];
        }
    }

    std::cout << etiqueta << ": ";
    bool primero = true;
    for (int i = 0; i < total; i++) {
        if (valores[i] == mejor) {
            if (!primero) {
                std::cout << SEPARADOR_NOMBRES;
            }
            std::cout << equipos[i].nombre;
            primero = false;
        }
    }
    std::cout << " (" << mejor << " " << descripcion << ")\n";
}

// Muestra la matriz de enfrentamientos, el mejor ataque y la mejor defensa.
inline void mostrarMatriz(const Equipo equipos[], int total,
                          const int goles[][MAX_EQUIPOS], bool simulado) {
    if (!reporteDisponible(simulado)) {
        return;
    }

    int golesFavor[MAX_EQUIPOS];
    int golesContra[MAX_EQUIPOS];
    for (int i = 0; i < total; i++) {
        golesFavor[i] = sumarFila(goles, total, i);
        golesContra[i] = sumarColumna(goles, total, i);
    }

    imprimirTitulo("MATRIZ DE ENFRENTAMIENTOS");
    imprimirMatriz(equipos, total, goles);
    std::cout << "\n";
    mostrarMejores(equipos, total, golesFavor, true, "Mejor ataque", "goles a favor");
    mostrarMejores(equipos, total, golesContra, false, "Mejor defensa", "goles en contra");
}