#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "utilerias.h"
#include "torneo.h"

// Revisa que el nombre tenga solo letras ASCII y digitos, y que mida
// entre MIN_CARACTERES_NOMBRE y MAX_CARACTERES_NOMBRE.
// Recibe: el nombre (const&, solo se lee) y 'motivo' (por referencia,
//         aqui se escribe la razon del rechazo).
// Devuelve: true si el nombre es valido.
inline bool nombreValido(const std::string& nombre, std::string& motivo) {
    for (std::size_t i = 0; i < nombre.size(); i++) {
        unsigned char c = static_cast<unsigned char>(nombre[i]);
        if (c > 127 || !std::isalnum(c)) {
            motivo = "solo se permiten letras sin acento ni enie y numeros, sin espacios.";
            return false;
        }
    }
    if (nombre.size() < static_cast<std::size_t>(MIN_CARACTERES_NOMBRE)) {
        motivo = "el nombre es muy corto (minimo "
                 + std::to_string(MIN_CARACTERES_NOMBRE) + " caracteres).";
        return false;
    }
    if (nombre.size() > static_cast<std::size_t>(MAX_CARACTERES_NOMBRE)) {
        motivo = "el nombre es muy largo (maximo "
                 + std::to_string(MAX_CARACTERES_NOMBRE) + " caracteres).";
        return false;
    }
    return true;
}
// Busca si ya hay un equipo con ese nombre, sin distinguir mayusculas.
// Recibe: el arreglo y el total como const, porque solo se leen.
// Devuelve: true si el nombre ya esta registrado.
inline bool nombreRepetido(const Equipo equipos[], int total,
                           const std::string& nombre) {
    for (int i = 0; i < total; i++) {
        if (mismoTexto(equipos[i].nombre, nombre)) {
            return true;
        }
    }
    return false;
}
// Revisa si una abreviatura ya la usa algun equipo registrado.
inline bool abreviaturaUsada(const Equipo equipos[], int total,
                             const std::string& abreviatura) {
    for (int i = 0; i < total; i++) {
        if (equipos[i].abreviatura == abreviatura) {
            return true;
        }
    }
    return false;
}

// Calcula una abreviatura de CARACTERES_ABREVIATURA letras que no se repita.
// Ejemplo: Pumas -> PUM; Pelicanos (si PEL existe) -> PEI.
inline std::string generarAbreviatura(const Equipo equipos[], int total,
                                      const std::string& nombre) {
    std::string mayus = aMayusculas(nombre);
    std::string base = mayus.substr(0, CARACTERES_ABREVIATURA);
    if (!abreviaturaUsada(equipos, total, base)) {
        return base;
    }

    std::string prefijo = mayus.substr(0, CARACTERES_ABREVIATURA - 1);
    for (std::size_t i = CARACTERES_ABREVIATURA; i < mayus.size(); i++) {
        std::string candidata = prefijo + mayus[i];
        if (!abreviaturaUsada(equipos, total, candidata)) {
            return candidata;
        }
    }
    for (char letra = 'A'; letra <= 'Z'; letra++) {
        std::string candidata = prefijo + letra;
        if (!abreviaturaUsada(equipos, total, candidata)) {
            return candidata;
        }
    }
    return base;  // no se alcanza: hay mas candidatas que equipos
}
// Registra un equipo: rechaza si la lista esta llena y pide el nombre
// hasta que sea valido y no repetido.
// Recibe: el arreglo (se modifica) y el total POR REFERENCIA (se incrementa).
// Devuelve: true si se registro, false si la lista estaba llena.
inline bool registrarEquipo(Equipo equipos[], int& total) {
    if (total >= MAX_EQUIPOS) {
        std::cout << "Lista llena: ya hay " << MAX_EQUIPOS
                  << " equipos registrados.\n";
        return false;
    }

    std::string nombre;
    std::string motivo;
    while (true) {
        nombre = leerCadena("Nombre del equipo " + std::to_string(total + 1) + ": ");
        if (!nombreValido(nombre, motivo)) {
            std::cout << "Nombre rechazado: " << motivo << "\n";
        } else if (nombreRepetido(equipos, total, nombre)) {
            std::cout << "Nombre rechazado: ya existe un equipo con ese nombre.\n";
        } else {
            break;
        }
    }

    Equipo nuevo;  // las estadisticas inician en 0 por el struct
    nuevo.nombre = nombre;
    nuevo.abreviatura = generarAbreviatura(equipos, total, nombre);
    equipos[total] = nuevo;
    total++;

    std::cout << "Equipo registrado: " << nuevo.nombre
              << " (" << nuevo.abreviatura << ")\n";
    return true;
}
// Imprime la lista de equipos en orden de registro.
// Recibe: el arreglo y el total como const, solo se leen.
inline void mostrarEquipos(const Equipo equipos[], int total) {
    if (total == 0) {
        std::cout << "No hay equipos registrados.\n";
        return;
    }

    std::cout << " EQUIPOS REGISTRADOS \n";
    std::cout << std::left << std::setw(4) << "#"
              << std::setw(17) << "EQUIPO" << "\n";
    for (int i = 0; i < total; i++) {
        std::cout << std::left << std::setw(4) << (i + 1)
                  << std::setw(17) << equipos[i].nombre << "\n";
    }
}