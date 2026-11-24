#pragma once

// =====================================================
// BASE COMUN DEL PROYECTO (bloque 0, de todo el equipo)
// =====================================================

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