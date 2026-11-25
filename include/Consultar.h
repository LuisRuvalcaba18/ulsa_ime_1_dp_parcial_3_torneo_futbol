#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "utilerias.h"
#include "torneo.h"
// Busca un equipo por nombre, sin distinguir mayusculas y minusculas.
// Recibe: el arreglo y el total como const, y el nombre buscado.
// Devuelve: apuntador al Equipo encontrado, o nullptr si no existe.
inline const Equipo* buscarEquipo(const Equipo equipos[], int total,
                                  const std::string& nombre) {
    for (int i = 0; i < total; i++) {
        if (mismoTexto(equipos[i].nombre, nombre)) {
            return &equipos[i];
        }
    }
    return nullptr;
}

// Texto del resultado desde la perspectiva del equipo consultado.
// Devuelve: "Ganado", "Empatado" o "Perdido".
inline std::string textoResultado(int golesPropios, int golesRival) {
    if (golesPropios > golesRival) {
        return "Ganado";
    }
    if (golesPropios == golesRival) {
        return "Empatado";
    }
    return "Perdido";
}

// Imprime las estadisticas del equipo usando el apuntador.
inline void imprimirEstadisticas(const Equipo* equipo) {
    std::cout << "Equipo: " << equipo->nombre << "\n";
    std::cout << "Jugados: " << equipo->jugados << "\n";
    std::cout << "Ganados: " << equipo->ganados << "\n";
    std::cout << "Empatados: " << equipo->empatados << "\n";
    std::cout << "Perdidos: " << equipo->perdidos << "\n";
    std::cout << "Goles a favor: " << equipo->golesFavor << "\n";
    std::cout << "Goles en contra: " << equipo->golesContra << "\n";
    std::cout << "Puntos: " << equipo->puntos << "\n";
}

// Imprime los partidos del equipo, con el marcador desde su lado.
// Los rivales salen en orden de registro porque los partidos se
// generaron en ese orden.
inline void imprimirPartidosDelEquipo(const Equipo equipos[], const Partido partidos[],
                                      int totalPartidos, int indiceEquipo) {
    std::cout << std::left << std::setw(ANCHO_NOMBRE) << "RIVAL"
              << std::setw(ANCHO_MARCADOR) << "MARCADOR"
              << "RESULTADO" << "\n";
    for (int i = 0; i < totalPartidos; i++) {
        if (juegaEnPartido(partidos[i], indiceEquipo)) {
            int propios = golesDelEquipo(partidos[i], indiceEquipo);
            int recibidos = golesDelRival(partidos[i], indiceEquipo);
            int rival = rivalDe(partidos[i], indiceEquipo);
            std::cout << std::left << std::setw(ANCHO_NOMBRE) << equipos[rival].nombre
                      << std::setw(ANCHO_MARCADOR) << textoMarcador(propios, recibidos)
                      << textoResultado(propios, recibidos) << "\n";
        }
    }
}

// Muestra la ficha completa del equipo encontrado.
// El indice del equipo se obtiene restando apuntadores:
// (direccion del equipo) - (direccion del inicio del arreglo).
inline void mostrarFicha(const Equipo equipos[], const Equipo* equipo,
                         const Partido partidos[], int totalPartidos) {
    int indiceEquipo = static_cast<int>(equipo - equipos);
    imprimirEstadisticas(equipo);
    std::cout << "\n";
    imprimirPartidosDelEquipo(equipos, partidos, totalPartidos, indiceEquipo);
}

// Pide un nombre, lo busca y muestra su ficha o el rechazo.
inline void consultarEquipo(const Equipo equipos[], int totalEquipos,
                            const Partido partidos[], int totalPartidos,
                            bool simulado) {
    if (!reporteDisponible(simulado)) {
        return;
    }

    std::string nombre = leerCadena("Nombre del equipo a consultar: ");
    const Equipo* encontrado = buscarEquipo(equipos, totalEquipos, nombre);

    imprimirTitulo("FICHA DE EQUIPO");
    if (encontrado == nullptr) {
        std::cout << "Equipo no encontrado: " << nombre << "\n";
        return;
    }
    mostrarFicha(equipos, encontrado, partidos, totalPartidos);
}