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