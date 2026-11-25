# Proyecto Parcial 3: Sistema de Gestion de un Torneo de Futbol

> Este README describe el trabajo del equipo y la integracion completa del proyecto.
> La guia completa se encuentra en [`PROYECTO.md`](PROYECTO.md).

## 1. Integrantes

| Modulo | Matricula | Nombre | Usuario de GitHub | Tema |
| --- | --- | --- | --- | --- |
| 1 | 26141 | Alan Rodrigo Guardiola Martinez | [Pendiente] | Registro de equipos |
| 2 | 26212 | Romeo Ramos Zertuche | romerz | Simulacion de partidos |
| 3 | [26221] | [Juan Antonio Rodriguez Zuñiga] | [Pendiente] | Tabla de posiciones |
| 4 | [26334] | [Manuel Mona Pèrez] | [manuelmona-star] | Clasificacion y campeon |
| 5 | [Pendiente] | [Pendiente] | [Pendiente] | Consultas |
| 6 | [Pendiente] | [Pendiente] | [Pendiente] | Matriz de enfrentamientos |

Si el equipo tiene cinco integrantes, el modulo 6 debe mostrar "Todo el equipo" en lugar de nombres individuales.

## 2. Opciones del menu

El programa repite el menu hasta que el usuario elige la opcion 9:

```text
1. Registrar equipo
2. Mostrar equipos
3. Simular torneo
4. Mostrar resultados
5. Mostrar tabla de posiciones
6. Mostrar campeon
7. Consultar equipo
8. Mostrar matriz de enfrentamientos
9. Salir
```

Las opciones invalidas muestran un rechazo y vuelven a presentar el menu.

## 3. Como compilar y ejecutar

Desde la carpeta del proyecto:

```bash
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o torneo
```

Para ejecutar en macOS o Linux:

```bash
./torneo
```

Para ejecutar en Windows:

```powershell
.\torneo.exe
```

## 4. Tipos de datos abstractos (TDA)

### Equipo

El registro `Equipo`, definido en `include/torneo.h`, guarda:

- Nombre y abreviatura.
- Partidos jugados, ganados, empatados y perdidos.
- Goles a favor y goles en contra.
- Puntos obtenidos.

Las operaciones principales son `reiniciarEstadisticas`, `registrarResultado`, `buscarEquipo` y las funciones de ordenamiento y consulta.

### Partido

El registro `Partido`, definido en `include/torneo.h`, guarda los indices del equipo local y del visitante, junto con sus goles.

Permite reutilizar operaciones comunes como `juegaEnPartido`, `golesDelEquipo`, `golesDelRival` y `rivalDe`.

Los equipos se almacenan en un arreglo de `Equipo`, los partidos en un arreglo de `Partido` y los goles en una matriz de `MAX_EQUIPOS x MAX_EQUIPOS`.

## 5. Reglas del programa

- Se pueden registrar hasta 6 equipos.
- Los nombres tienen entre 3 y 15 caracteres, solo usan letras ASCII sin acentos ni `ñ` y numeros.
- Los nombres no pueden repetirse sin distinguir mayusculas y minusculas.
- Las abreviaturas tienen 3 caracteres. Se generan a partir del nombre y se buscan alternativas si ya estan en uso.
- Se generan 15 partidos al enfrentarse todos los equipos una sola vez.
- Victoria: 3 puntos. Empate: 1 punto. Derrota: 0 puntos.
- El torneo se simula una sola vez por ejecucion.
- La tabla se calcula automaticamente al terminar la simulacion.
- La tabla se ordena de mayor a menor por puntos.
- Los equipos empatados pueden conservar el orden de registro.
- Los reportes no estan disponibles hasta simular el torneo.
- Para simular se necesitan exactamente 6 equipos.
- Si hay empate en el primer lugar, el usuario puede elegir al campeon.
- El mejor ataque usa goles a favor y el mejor defensa usa goles en contra.

## 6. Equipos del escenario

Los 6 equipos registrados en el escenario obligatorio son:

| # | Nombre | Abreviatura |
| --- | --- | --- |
| 1 | Aguilas | AGU |
| 2 | Halcones | HAL |
| 3 | Jaguares | JAG |
| 4 | Leones | LEO |
| 5 | Pumas | PUM |
| 6 | Tigres | TIG |

## 7. Calculo a mano

Se ejecuta una corrida en modo aleatorio y se obtuvieron los siguientes resultados:

```text
1. Aguilas          5 - 4     Halcones
2. Aguilas          2 - 3     Jaguares
3. Aguilas          0 - 4     Leones
4. Aguilas          3 - 2     Pumas
5. Aguilas          2 - 2     Tigres
6. Halcones         1 - 0     Jaguares
7. Halcones         2 - 3     Leones
8. Halcones         5 - 2     Pumas
9. Halcones         3 - 4     Tigres
10. Jaguares         5 - 1     Leones
11. Jaguares         1 - 1     Pumas
12. Jaguares         2 - 1     Tigres
13. Leones           4 - 4     Pumas
14. Leones           0 - 0     Tigres
15. Pumas            0 - 0     Tigres
```

Antes de consultar los reportes, el calculo manual de la tabla es:

| Equipo | PJ | PG | PE | PP | GF | GC | PTS |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Jaguares | 5 | 3 | 1 | 1 | 11 | 6 | 10 |
| Leones | 5 | 2 | 2 | 1 | 12 | 11 | 8 |
| Aguilas | 5 | 2 | 1 | 2 | 12 | 15 | 7 |
| Halcones | 5 | 2 | 0 | 3 | 15 | 14 | 6 |
| Tigres | 5 | 1 | 3 | 1 | 7 | 7 | 6 |
| Pumas | 5 | 0 | 3 | 2 | 9 | 13 | 3 |

**Campeon:** Jaguares, con 10 puntos.  
**Mejor ataque:** Halcones, con 15 goles a favor.  
**Mejor defensa:** Jaguares, con 6 goles en contra.

**Comparacion con la salida del programa:** los 15 marcadores, la tabla de posiciones, el campeon, el mejor ataque y el mejor defensa coincidieron con el calculo manual.

## 8. Receta del menu

```text
INICIO

Crear el arreglo equipos con capacidad MAX_EQUIPOS.
Crear el arreglo partidos con capacidad TOTAL_PARTIDOS.
Crear la matriz goles[MAX_EQUIPOS][MAX_EQUIPOS].
Iniciar totalEquipos en 0.
Iniciar totalPartidos en 0.
Iniciar torneoSimulado en falso.

REPETIR
    Mostrar el menu.
    Leer opcion con leerEntero.

    SEGUN opcion:
        1: registrarEquipo(equipos, totalEquipos)
        2: mostrarEquipos(equipos, totalEquipos)
        3: si simularTorneo(...) fue exitoso:
               calcularTabla(...)
               llenarMatriz(...)
        4: mostrarResultados(...)
        5: mostrarTabla(...)
        6: mostrarCampeon(...)
        7: consultarEquipo(...)
        8: mostrarMatriz(...)
        9: mostrar "Hasta luego."
        OTRO: mostrar mensaje de opcion no valida

MIENTRAS opcion no sea 9.

FIN
```

## 9. Documentacion individual

| Modulo | Documentacion | Propuesta de mejora |
| --- | --- | --- |
| 1 | [Pendiente: docs/26141/modulo.md] | [26141: propuesta](docs/mejoras/26141) |
| 2 | [26212: simulacion de partidos](docs/26212/modulo.md) | [26212: estadisticas del torneo](docs/mejoras/26212/mejora.md) |
| 3 | [Pendiente] | [Pendiente] |
| 4 | [26334: clasificaciòn y campeòn] (docs/mejoras/26334/mejora.md) | [Tabla de posiciones automatica] |
| 5 | [Pendiente] | [Pendiente] |
| 6 | [Pendiente: equipos de 5 usan docs/modulo_6/modulo.md] | Sin propuesta adicional en equipos de 5 |

Las propuestas disponibles actualmente son:

- [Alan Rodrigo Guardiola Martinez - propuesta 26141](docs/mejoras/26141)
- [Manuel Mona Perez - tabla de posiciones automatica](docs/mejoras/26334)
- [Romeo Ramos Zertuche - estadisticas generales del torneo](docs/mejoras/26212/mejora.md)

## 10. Cambios a la base comun

Sin cambios a las constantes ni a los registros compartidos de `include/torneo.h`.
