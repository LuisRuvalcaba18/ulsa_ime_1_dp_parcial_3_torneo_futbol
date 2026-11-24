#pragma once

// =====================================================
// BASE COMUN DEL PROYECTO (bloque 0, de todo el equipo)
//
// Este archivo trae las constantes que todos los modulos comparten.
// El equipo agrega aqui, debajo de las constantes:
//   1. Los registros (struct) que disenen para el torneo.
//   2. Las funciones que varios modulos necesiten.
//
// Si cambian una constante, anotenlo en el README del equipo.
// =====================================================

#include <string>

// ---------- Constantes compartidas ----------
// Una constante no es una variable global: su valor nunca cambia.

// Cantidad de equipos del torneo.
const int MAX_EQUIPOS = 6;

// Cantidad de partidos: todos contra todos, a una vuelta.
const int TOTAL_PARTIDOS = 15;

// Longitud minima y maxima del nombre de un equipo.
const int MIN_CARACTERES_NOMBRE = 3;
const int MAX_CARACTERES_NOMBRE = 15;

// Longitud de la abreviatura de un equipo.
const int CARACTERES_ABREVIATURA = 3;

// Puntos que recibe un equipo por cada resultado.
const int PUNTOS_VICTORIA = 3;
const int PUNTOS_EMPATE = 1;
const int PUNTOS_DERROTA = 0;

// ---------- Registros (equipo) ----------
// Escriban aqui los struct del torneo.
#include <string>
#include <cctype>

struct Equipo {
    std::string nombre;
    std::string abreviatura;
    int jugados = 0;
    int ganados = 0;
    int empatados = 0;
    int perdidos = 0;
    int golesFavor = 0;
    int golesContra = 0;
    int puntos = 0;
};

struct Partido {
    int local = 0;          // indice del equipo local en el arreglo
    int visitante = 0;      // indice del equipo visitante
    int golesLocal = 0;
    int golesVisitante = 0;
};

// Convierte un texto a mayusculas (devuelve una copia).
inline std::string aMayusculas(const std::string& texto) {
    std::string resultado = texto;
    for (std::size_t i = 0; i < resultado.size(); i++) {
        resultado[i] = static_cast<char>(
            std::toupper(static_cast<unsigned char>(resultado[i])));
    }
    return resultado;
}

// Compara dos textos sin distinguir mayusculas y minusculas.
inline bool mismoTexto(const std::string& a, const std::string& b) {
    return aMayusculas(a) == aMayusculas(b);
}
// ---------- Funciones comunes (equipo) ----------
// Escriban aqui las funciones que varios modulos comparten.
