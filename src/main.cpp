// Proyecto Parcial 3: Sistema de Gestión de un Torneo de Futbol
// Programa principal (bloque de integración, de todo el equipo).

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#include "utilerias.h"
#include "torneo.h"
#include "registro_equipos.h"
#include "escenario_prueba.h"

using namespace std;

int main() {

    // =====================================================
    // DATOS DEL TORNEO
    // =====================================================

    Equipo equipos[MAX_EQUIPOS];
    Partido partidos[TOTAL_PARTIDOS];

    int cantidadEquipos = 0;
    bool torneoSimulado = false;

    srand(static_cast<unsigned>(time(nullptr)));

    int opcion;

    // =====================================================
    // MENU PRINCIPAL
    // =====================================================

    do {

        cout << "\n============================================\n";
        cout << "       TORNEO DE FUTBOL - PARCIAL 3\n";
        cout << "============================================\n";
        cout << "1. Registrar equipos\n";
        cout << "2. Mostrar equipos\n";
        cout << "3. Simular torneo\n";
        cout << "4. Mostrar resultados\n";
        cout << "5. Mostrar tabla de posiciones\n";
        cout << "6. Mostrar matriz de resultados\n";
        cout << "7. Mostrar campeon\n";
        cout << "8. Consultar equipo\n";
        cout << "9. Salir\n";
        cout << "============================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(1000, '\n');

        // =================================================
        // OPCION 1 - REGISTRAR EQUIPOS
        // =================================================

        if (opcion == 1) {

            if (cantidadEquipos >= MAX_EQUIPOS) {
                cout << "\nRECHAZO: ya se registraron los "
                     << MAX_EQUIPOS << " equipos.\n";
            }
            else {

                string nombre;
                string abreviatura;
                string motivo;

                cout << "\n--- REGISTRO DE EQUIPO ---\n";

                cout << "Nombre del equipo: ";
                getline(cin, nombre);

                if (!nombreValido(nombre, motivo)) {
                    cout << "RECHAZO: " << motivo << "\n";
                }
                else {

                    // Revisar que no exista repetido
                    bool repetido = false;

                    for (int i = 0; i < cantidadEquipos; i++) {
                        if (mismoTexto(equipos[i].nombre, nombre)) {
                            repetido = true;
                            break;
                        }
                    }

                    if (repetido) {
                        cout << "RECHAZO: ese equipo ya esta registrado.\n";
                    }
                    else {

                        cout << "Abreviatura de 3 caracteres: ";
                        getline(cin, abreviatura);

                        if (abreviatura.size() != CARACTERES_ABREVIATURA) {
                            cout << "RECHAZO: la abreviatura debe tener "
                                 << CARACTERES_ABREVIATURA
                                 << " caracteres.\n";
                        }
                        else {

                            equipos[cantidadEquipos].nombre = nombre;
                            equipos[cantidadEquipos].abreviatura =
                                aMayusculas(abreviatura);

                            cantidadEquipos++;

                            cout << "Equipo registrado correctamente.\n";
                        }
                    }
                }
            }
        }

        // =================================================
        // OPCION 2 - MOSTRAR EQUIPOS
        // =================================================

        else if (opcion == 2) {

            if (cantidadEquipos == 0) {
                cout << "\nRECHAZO: no hay equipos registrados.\n";
            }
            else {

                cout << "\n========== EQUIPOS ==========\n";

                for (int i = 0; i < cantidadEquipos; i++) {

                    cout << i + 1 << ". "
                         << equipos[i].nombre
                         << " ("
                         << equipos[i].abreviatura
                         << ")\n";
                }
            }
        }

        // =================================================
        // OPCION 3 - SIMULAR TORNEO
        // =================================================

        else if (opcion == 3) {

            if (cantidadEquipos < MAX_EQUIPOS) {

                cout << "\nRECHAZO: se necesitan "
                     << MAX_EQUIPOS
                     << " equipos para simular el torneo.\n";
            }
            else if (torneoSimulado) {

                cout << "\nRECHAZO: el torneo ya fue simulado.\n";
            }
            else {

                cout << "\n--- SIMULANDO TORNEO ---\n";

                int indicePartido = 0;

                // Todos contra todos
                for (int i = 0; i < MAX_EQUIPOS - 1; i++) {

                    for (int j = i + 1; j < MAX_EQUIPOS; j++) {

                        partidos[indicePartido].local = i;
                        partidos[indicePartido].visitante = j;

                        partidos[indicePartido].golesLocal =
                            rand() % 6;

                        partidos[indicePartido].golesVisitante =
                            rand() % 6;

                        indicePartido++;
                    }
                }

                // Reiniciar estadisticas
                for (int i = 0; i < MAX_EQUIPOS; i++) {

                    equipos[i].jugados = 0;
                    equipos[i].ganados = 0;
                    equipos[i].empatados = 0;
                    equipos[i].perdidos = 0;
                    equipos[i].golesFavor = 0;
                    equipos[i].golesContra = 0;
                    equipos[i].puntos = 0;
                }

                // Procesar partidos
                for (int i = 0; i < TOTAL_PARTIDOS; i++) {

                    int local = partidos[i].local;
                    int visitante = partidos[i].visitante;

                    int golesLocal =
                        partidos[i].golesLocal;

                    int golesVisitante =
                        partidos[i].golesVisitante;

                    equipos[local].jugados++;
                    equipos[visitante].jugados++;

                    equipos[local].golesFavor += golesLocal;
                    equipos[local].golesContra += golesVisitante;

                    equipos[visitante].golesFavor += golesVisitante;
                    equipos[visitante].golesContra += golesLocal;

                    if (golesLocal > golesVisitante) {

                        equipos[local].ganados++;
                        equipos[local].puntos += PUNTOS_VICTORIA;

                        equipos[visitante].perdidos++;
                        equipos[visitante].puntos += PUNTOS_DERROTA;
                    }
                    else if (golesVisitante > golesLocal) {

                        equipos[visitante].ganados++;
                        equipos[visitante].puntos += PUNTOS_VICTORIA;

                        equipos[local].perdidos++;
                        equipos[local].puntos += PUNTOS_DERROTA;
                    }
                    else {

                        equipos[local].empatados++;
                        equipos[visitante].empatados++;

                        equipos[local].puntos += PUNTOS_EMPATE;
                        equipos[visitante].puntos += PUNTOS_EMPATE;
                    }
                }

                torneoSimulado = true;

                cout << "\nTorneo simulado correctamente.\n";
            }
        }

        // =================================================
        // OPCION 4 - RESULTADOS
        // =================================================

        else if (opcion == 4) {

            if (!torneoSimulado) {

                cout << "\nRECHAZO: primero debes simular el torneo.\n";
            }
            else {

                cout << "\n========== RESULTADOS ==========\n";

                for (int i = 0; i < TOTAL_PARTIDOS; i++) {

                    cout << equipos[partidos[i].local].nombre
                         << " "
                         << partidos[i].golesLocal
                         << " - "
                         << partidos[i].golesVisitante
                         << " "
                         << equipos[partidos[i].visitante].nombre
                         << "\n";
                }
            }
        }

        // =================================================
        // OPCION 5 - TABLA
        // =================================================

        else if (opcion == 5) {

            if (!torneoSimulado) {

                cout << "\nRECHAZO: primero debes simular el torneo.\n";
            }
            else {

                cout << "\n================ TABLA DE POSICIONES ================\n";

                cout << left
                     << setw(5) << "#"
                     << setw(18) << "Equipo"
                     << setw(5) << "PJ"
                     << setw(5) << "G"
                     << setw(5) << "E"
                     << setw(5) << "P"
                     << setw(6) << "GF"
                     << setw(6) << "GC"
                     << setw(6) << "PTS"
                     << "\n";

                cout << "------------------------------------------------------\n";

                // Copia para ordenar sin modificar los equipos
                Equipo tabla[MAX_EQUIPOS];

                for (int i = 0; i < MAX_EQUIPOS; i++) {
                    tabla[i] = equipos[i];
                }

                // Ordenar por puntos
                for (int i = 0; i < MAX_EQUIPOS - 1; i++) {

                    for (int j = i + 1; j < MAX_EQUIPOS; j++) {

                        if (tabla[j].puntos > tabla[i].puntos) {

                            Equipo temporal = tabla[i];
                            tabla[i] = tabla[j];
                            tabla[j] = temporal;
                        }
                    }
                }

                for (int i = 0; i < MAX_EQUIPOS; i++) {

                    cout << left
                         << setw(5) << i + 1
                         << setw(18) << tabla[i].nombre
                         << setw(5) << tabla[i].jugados
                         << setw(5) << tabla[i].ganados
                         << setw(5) << tabla[i].empatados
                         << setw(5) << tabla[i].perdidos
                         << setw(6) << tabla[i].golesFavor
                         << setw(6) << tabla[i].golesContra
                         << setw(6) << tabla[i].puntos
                         << "\n";
                }
            }
        }

        // =================================================
        // OPCION 6 - MATRIZ
        // =================================================

        else if (opcion == 6) {

            if (!torneoSimulado) {

                cout << "\nRECHAZO: primero debes simular el torneo.\n";
            }
            else {

                cout << "\n========== MATRIZ DE RESULTADOS ==========\n\n";

                cout << setw(12) << "";

                for (int i = 0; i < MAX_EQUIPOS; i++) {
                    cout << setw(8) << equipos[i].abreviatura;
                }

                cout << "\n";

                for (int i = 0; i < MAX_EQUIPOS; i++) {

                    cout << setw(12) << equipos[i].abreviatura;

                    for (int j = 0; j < MAX_EQUIPOS; j++) {

                        if (i == j) {

                            cout << setw(8) << "-";
                        }
                        else {

                            bool encontrado = false;

                            for (int k = 0; k < TOTAL_PARTIDOS; k++) {

    Partido* partido = partidos + k;

    if (partido->local == i &&
        partido->visitante == j) {

        cout << setw(8)
             << to_string(partido->golesLocal)
             + "-" +
             to_string(partido->golesVisitante);

        encontrado = true;
        break;
    }

    if (partido->local == j &&
        partido->visitante == i) {

        cout << setw(8)
             << to_string(partido->golesVisitante)
             + "-" +
             to_string(partido->golesLocal);

        encontrado = true;
        break;
    }
}

if (!encontrado) {
    cout << setw(8) << "-";
}
        }

        // =================================================
        // OPCION 7 - CAMPEON
        // =================================================

        else if (opcion == 7) {

            if (!torneoSimulado) {

                cout << "\nRECHAZO: primero debes simular el torneo.\n";
            }
            else {

                int mejor = 0;

                for (int i = 1; i < MAX_EQUIPOS; i++) {

                    if (equipos[i].puntos > equipos[mejor].puntos) {
                        mejor = i;
                    }
                }

                cout << "\n========== CAMPEON ==========\n";
                cout << "Equipo: "
                     << equipos[mejor].nombre
                     << "\n";
                cout << "Puntos: "
                     << equipos[mejor].puntos
                     << "\n";
            }
        }

        // =================================================
        // OPCION 8 - CONSULTAR EQUIPO
        // =================================================

        else if (opcion == 8) {

            if (cantidadEquipos == 0) {

                cout << "\nRECHAZO: no hay equipos registrados.\n";
            }
            else {

                string nombreBusqueda;

                cout << "\nNombre del equipo a consultar: ";
                getline(cin, nombreBusqueda);

                int encontrado = -1;

                for (int i = 0; i < cantidadEquipos; i++) {

                    if (mismoTexto(
                            equipos[i].nombre,
                            nombreBusqueda)) {

                        encontrado = i;
                        break;
                    }
                }

                if (encontrado == -1) {

                    cout << "RECHAZO: equipo no encontrado.\n";
                }
                else {

                    cout << "\nEquipo encontrado:\n";
                    cout << "Nombre: "
                         << equipos[encontrado].nombre
                         << "\n";
                    cout << "Abreviatura: "
                         << equipos[encontrado].abreviatura
                         << "\n";
                    cout << "Partidos jugados: "
                         << equipos[encontrado].jugados
                         << "\n";
                    cout << "Ganados: "
                         << equipos[encontrado].ganados
                         << "\n";
                    cout << "Empatados: "
                         << equipos[encontrado].empatados
                         << "\n";
                    cout << "Perdidos: "
                         << equipos[encontrado].perdidos
                         << "\n";
                    cout << "Puntos: "
                         << equipos[encontrado].puntos
                         << "\n";
                }
            }
        }

        // =================================================
        // OPCION 9 - SALIR
        // =================================================

        else if (opcion == 9) {

            cout << "\nSaliendo del programa...\n";
        }

        // =================================================
        // OPCION INVALIDA
        // =================================================

        else {

            cout << "\nRECHAZO: opcion de menu inexistente.\n";
            opcion = 9;
        }

    } while (opcion != 9);

    return 0;
}