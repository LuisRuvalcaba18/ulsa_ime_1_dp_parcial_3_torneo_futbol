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

// Ancho de cada columna de los reportes (PROYECTO.md, seccion 2.6):
// # = 4, POS = 5, EQUIPO/LOCAL/RIVAL = 17, MARCADOR = 10,
// PJ/PG/PE/PP/GF/GC = 4, PTS = 5 y cada columna de la matriz = 6.
const int ANCHO_NUMERO = 4;       
const int ANCHO_POSICION = 5;     
const int ANCHO_NOMBRE = 17;     
const int ANCHO_MARCADOR = 10;    
const int ANCHO_ESTADISTICA = 4;  
const int ANCHO_PUNTOS = 5;       
const int ANCHO_CELDA = 6;        
// ---------- Registros ----------

// Datos: nombre, abreviatura y estadisticas del torneo.
// Operaciones: registrarEquipo (modulo 1), reiniciarEstadisticas y
// registrarResultado (modulo 3), buscarEquipo (modulo 5).
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

// Datos: indices del equipo local y visitante en el arreglo de equipos
// y los goles de cada uno.
// Operaciones: juegaEnPartido, golesDelEquipo, golesDelRival y rivalDe.
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

// Arma el texto de un marcador, por ejemplo "3 - 1", para que setw
// lo trate como un solo dato.
// Recibe: goles del primer equipo y goles del segundo.
// Devuelve: el marcador como texto.
inline std::string textoMarcador(int golesPrimero, int golesSegundo) {
    return std::to_string(golesPrimero) + " - " + std::to_string(golesSegundo);
}

// Imprime el titulo de un reporte con el formato "--- TITULO ---".
// Recibe: el titulo sin guiones, por ejemplo "TABLA DE POSICIONES".
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

// Revisa si ya se puede mostrar un reporte del torneo.
// checa si el torneo ya se simulo.
// Devuelve true si se puede mostrar; si no, avisa y devuelve false.
inline bool reporteDisponible(bool torneoSimulado) {
    if (!torneoSimulado) {
        std::cout << "Reporte no disponible: primero hay que simular el torneo.\n";
        return false;
    }
    return true;
}