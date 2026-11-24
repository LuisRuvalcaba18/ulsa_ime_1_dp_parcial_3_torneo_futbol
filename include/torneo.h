#pragma once

// =====================================================
// BASE COMUN DEL PROYECTO (bloque 0, de todo el equipo)
// =====================================================
#include <iostream>
#include <string>
#include <cctype>

// ---------- Constantes compartidas ----------
const int MAX_EQUIPOS = 6;
const int TOTAL_PARTIDOS = 15;
const int MIN_CARACTERES_NOMBRE = 3;
const int MAX_CARACTERES_NOMBRE = 15;
const int CARACTERES_ABREVIATURA = 3;
const int PUNTOS_VICTORIA = 3;
const int PUNTOS_EMPATE = 1;
const int PUNTOS_DERROTA = 0;
const int ANCHO_NUMERO = 4;       
const int ANCHO_POSICION = 5;     
const int ANCHO_NOMBRE = 17;     
const int ANCHO_MARCADOR = 10;    
const int ANCHO_ESTADISTICA = 4;  
const int ANCHO_PUNTOS = 5;       
const int ANCHO_CELDA = 6;        
// ---------- Registros ----------
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
    int local = 0;
    int visitante = 0;
    int golesLocal = 0;
    int golesVisitante = 0;
};

// ---------- Funciones comunes ----------

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

inline std::string textoMarcador(int golesPrimero, int golesSegundo) {
    return std::to_string(golesPrimero) + " - " + std::to_string(golesSegundo);
}

inline void imprimirTitulo(const std::string& titulo) {
    std::cout << "--- " << titulo << " ---\n";
}
// ---------- Operaciones del TDA Partido ----------
// Reciben el partido como const& (solo se lee) y el indice de un
// equipo en el arreglo de equipos.
// Devuelve: true si el equipo jugo ese partido.
inline bool juegaEnPartido(const Partido& partido, int indiceEquipo) {
    return partido.local == indiceEquipo || partido.visitante == indiceEquipo;
}
// Devuelve: los goles que anoto el equipo en ese partido.
inline int golesDelEquipo(const Partido& partido, int indiceEquipo) {
    if (partido.local == indiceEquipo) {
        return partido.golesLocal;
    }
    return partido.golesVisitante;
}
// Devuelve: los goles que recibio el equipo en ese partido.
inline int golesDelRival(const Partido& partido, int indiceEquipo) {
    if (partido.local == indiceEquipo) {
        return partido.golesVisitante;
    }
    return partido.golesLocal;
}
// Devuelve: el indice del rival del equipo en ese partido.
inline int rivalDe(const Partido& partido, int indiceEquipo) {
    if (partido.local == indiceEquipo) {
        return partido.visitante;
    }
    return partido.local;
}