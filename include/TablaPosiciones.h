#pragma once

// =====================================================
// MODULO 3: TABLA DE POSICIONES
// Responsable: Juan
// Calcula las estadisticas de cada equipo a partir de los partidos.
// No imprime ningun reporte: solo actualiza los registros Equipo.
// =====================================================
#include "torneo.h"

// Deja en cero las estadisticas de un equipo, sin tocar nombre ni abreviatura.
// Recibe: el equipo POR REFERENCIA, porque se modifica.
inline void reiniciarEstadisticas(Equipo& equipo) {
    equipo.jugados = 0;
    equipo.ganados = 0;
    equipo.empatados = 0;
    equipo.perdidos = 0;
    equipo.golesFavor = 0;
    equipo.golesContra = 0;
    equipo.puntos = 0;
}
// Operacion "registrar resultado" del TDA Equipo.
// Suma un partido jugado, los goles y los puntos que le tocan.
// Recibe: el equipo POR REFERENCIA (se modifica) y los goles por valor.
inline void registrarResultado(Equipo& equipo, int golesFavor, int golesContra) {
    equipo.jugados++;
    equipo.golesFavor += golesFavor;
    equipo.golesContra += golesContra;

    if (golesFavor > golesContra) {
        equipo.ganados++;
        equipo.puntos += PUNTOS_VICTORIA;
    } else if (golesFavor == golesContra) {
        equipo.empatados++;
        equipo.puntos += PUNTOS_EMPATE;
    } else {
        equipo.perdidos++;
        equipo.puntos += PUNTOS_DERROTA;
    }
}
