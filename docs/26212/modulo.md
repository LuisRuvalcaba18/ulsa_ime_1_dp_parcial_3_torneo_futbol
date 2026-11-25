# Documentación del módulo

## 1. Autor

**Nombre:** Romeo Ramos Zertuche  
**Matrícula:** 26212  
**Módulo:** 2. Simulación de partidos  
**Archivo de código:** `include/simulacion.h`

## 2. Propósito

Mi módulo genera los 15 partidos del torneo: los 6 equipos juegan todos contra todos a una vuelta. Cada partido se puede jugar en **modo aleatorio**, donde cada equipo anota de 0 a 5 goles al azar, o en **modo de prueba**, con los 15 marcadores fijos de `escenario_prueba.h`. También muestra el reporte de resultados de los partidos.

Al usuario le sirve porque los partidos son la base de todo lo demás: con ellos se calcula la tabla, se elige al campeón, se arma la ficha de cada equipo y se llena la matriz. El modo de prueba permite comparar la salida del programa con los ejemplos de `PROYECTO.md`.

El torneo solo se simula **una vez por ejecución** y solo con los **6 equipos** registrados.

## 3. Entradas y salidas

| Función | Recibe | Produce |
| --- | --- | --- |
| `simularTorneo` | El arreglo `partidos` (se llena), `totalPartidos` y `simulado` por referencia (se actualizan) y `totalEquipos` por valor | Devuelve `true` si simuló o `false` si rechazó. Imprime el rechazo o "Torneo simulado: se jugaron 15 partidos." |
| `leerModoSimulacion` | Del teclado: el modo (1 o 2) | Devuelve `MODO_ALEATORIO` o `MODO_PRUEBA` |
| `generarPartidos` | El arreglo `partidos` (se llena), `totalEquipos` y `modo` | Devuelve cuántos partidos generó (15) |
| `imprimirPartido` | El número de partido, el partido como `const&` y los equipos como `const` | Imprime un renglón del reporte |
| `mostrarResultados` | Los equipos y los partidos como `const`, `totalPartidos` y `simulado` | Imprime el reporte "RESULTADOS DE LOS PARTIDOS" o el rechazo |

## 4. Decisiones de diseño

**¿Qué funciones tiene tu módulo y qué tarea hace cada una?**

- `leerModoSimulacion`: pregunta el modo y lo vuelve a pedir hasta que sea 1 o 2.
- `generarPartidos`: arma los 15 partidos con dos ciclos anidados y les pone los goles según el modo.
- `simularTorneo`: revisa los rechazos (ya simulado, faltan equipos), pide el modo, genera los partidos y marca el torneo como simulado.
- `imprimirPartido`: imprime un solo renglón del reporte con el ancho de cada columna.
- `mostrarResultados`: revisa que ya se haya simulado, imprime el título y el encabezado, y llama a `imprimirPartido` por cada partido.

Separé leer el modo, generar los partidos e imprimir un renglón en funciones distintas para que cada una tenga **una sola tarea**.

**¿Qué estructuras de datos usa tu módulo (registros, arreglos, matrices o apuntadores), por qué las elegiste y cómo pasas los datos a cada función (por valor, por referencia, como arreglo o con un apuntador)?**

- **Registro `Partido`:** guarda el índice del equipo local, el índice del visitante y los goles de cada uno. Guardo **índices** y no los nombres para no duplicar datos: el nombre y las estadísticas viven una sola vez en el arreglo de `Equipo`.
- **Arreglo de registros `Partido partidos[TOTAL_PARTIDOS]`:** se declara en `main` y mi módulo lo llena. Se pasa como arreglo, o sea, la dirección de su primer elemento, por eso la función puede llenar el arreglo original.
- **Matriz `GOLES_PRUEBA[TOTAL_PARTIDOS][COLUMNAS_MARCADOR]`** de `escenario_prueba.h`: de ahí leo los marcadores del modo de prueba. La fila es el número de partido y la columna es local o visitante.
- **Por referencia:** `totalPartidos` y `simulado`, porque `simularTorneo` los cambia y el cambio debe verse en `main`.
- **Por valor:** `totalEquipos` y `modo`, porque solo se leen.
- **Como `const`:** los arreglos en `mostrarResultados` y el partido en `imprimirPartido` (`const Partido&`), porque solo se leen. El `&` evita copiar el registro.

**¿Dónde demuestras los temas asignados a tu módulo?**

- **Registros:** en `generarPartidos` se crea un `Partido`, se llenan sus campos (`local`, `visitante`, `golesLocal`, `golesVisitante`) y se guarda en el arreglo.
- **Ciclos anidados:** en `generarPartidos`. El ciclo de afuera recorre al equipo local y el de adentro recorre a los visitantes que van **después** de él (`visitante = local + 1`). Así cada pareja juega una sola vez y nadie juega contra sí mismo: 5 + 4 + 3 + 2 + 1 = 15 partidos. Ese orden es el mismo de `GOLES_PRUEBA`, por eso el partido `numero` usa la fila `numero`.

**¿Qué ciclos usaste y por qué esos?**

- **`for` anidados** en `generarPartidos`, porque sé exactamente cuántas vueltas da cada ciclo.
- **`while`** en `leerModoSimulacion`, porque no sé cuántas veces se va a equivocar el usuario: se repite mientras el modo no sea válido.
- **`for`** en `mostrarResultados`, para recorrer los 15 partidos del arreglo.

**¿Qué constantes usaste y por qué son constantes?**

- Mías: `MODO_ALEATORIO = 1`, `MODO_PRUEBA = 2`, `COLUMNA_GOLES_LOCAL = 0` y `COLUMNA_GOLES_VISITANTE = 1`.
- De `torneo.h`: `MAX_EQUIPOS`, `TOTAL_PARTIDOS`, `ANCHO_NUMERO`, `ANCHO_NOMBRE` y `ANCHO_MARCADOR`.

Son constantes porque su valor nunca cambia durante el programa. Con nombre se entiende qué significa cada número, y si hay que cambiar uno se cambia en un solo lugar.

**¿Qué funciones reutilizaste de `utilerias.h`, de `torneo.h` o de otro módulo?**

- De `utilerias.h`: `leerEntero` para leer el modo y `numeroAleatorio` para los goles del modo aleatorio.
- De `torneo.h`: los registros `Partido` y `Equipo`, `reporteDisponible`, `imprimirTitulo` y `textoMarcador`. `textoMarcador` la escribí yo en `torneo.h` porque también la usa el módulo de consultas.
- De `escenario_prueba.h`: la matriz `GOLES_PRUEBA`.

**¿Qué casos de rechazo maneja tu módulo y qué mensaje muestra en cada uno?**

| Caso | Mensaje |
| --- | --- |
| Simular cuando ya se simuló | `Rechazado: el torneo ya se simulo. Solo se simula una vez por ejecucion.` |
| Simular sin los 6 equipos | `Rechazado: se necesitan 6 equipos para simular y hay N.` |
| Modo que no existe (0, 3, -1...) | `Modo no valido. Escribe 1 o 2.` y vuelve a preguntar |
| Modo con texto o decimales | `Entrada no valida. Escribe un numero entero.` (de `leerEntero`) y vuelve a preguntar |
| Ver resultados antes de simular | `Reporte no disponible: primero hay que simular el torneo.` |

## 5. Receta

```
simularTorneo(partidos, totalPartidos por referencia, totalEquipos, simulado por referencia):
    si simulado:
        avisar "el torneo ya se simulo" y regresar falso
    si totalEquipos < MAX_EQUIPOS:
        avisar "se necesitan 6 equipos y hay totalEquipos" y regresar falso
    modo = leerModoSimulacion()
    totalPartidos = generarPartidos(partidos, totalEquipos, modo)
    simulado = verdadero
    avisar "Torneo simulado: se jugaron totalPartidos partidos"
    regresar verdadero

leerModoSimulacion():
    mostrar "1. Modo aleatorio" y "2. Modo de prueba"
    leer modo con leerEntero
    mientras modo no sea 1 ni 2:
        avisar "Modo no valido" y volver a leer modo
    regresar modo

generarPartidos(partidos, totalEquipos, modo):
    numero = 0
    para local desde 0 hasta totalEquipos - 1:
        para visitante desde local + 1 hasta totalEquipos - 1:
            crear un Partido con local y visitante
            si modo es de prueba:
                golesLocal = GOLES_PRUEBA[numero][0]
                golesVisitante = GOLES_PRUEBA[numero][1]
            si no:
                golesLocal = numeroAleatorio()
                golesVisitante = numeroAleatorio()
            guardar el partido en partidos[numero]
            numero = numero + 1
    regresar numero

mostrarResultados(equipos, partidos, totalPartidos, simulado):
    si no simulado:
        avisar "Reporte no disponible" y regresar
    imprimir "--- RESULTADOS DE LOS PARTIDOS ---"
    imprimir encabezado: #, LOCAL, MARCADOR, VISITANTE
    para i desde 0 hasta totalPartidos - 1:
        imprimirPartido(i + 1, partidos[i], equipos)

imprimirPartido(numero, partido, equipos):
    imprimir numero (ancho 4), nombre del local (ancho 17),
    marcador "golesLocal - golesVisitante" (ancho 10) y nombre del visitante
```

**¿Probaste tu receta a mano con los datos del escenario? ¿Qué corregiste?**

Sí. Seguí los ciclos a mano en modo de prueba: con `local = 0` y `visitante = 1` sale el partido 1, que usa la fila 0 de `GOLES_PRUEBA` (Aguilas 3 - 3 Halcones). La última combinación, `local = 4` y `visitante = 5`, es el partido 15 y usa la fila 14 (Pumas 0 - 1 Tigres). Así comprobé que el orden de los ciclos coincide con el orden de los marcadores de prueba y que salen exactamente 15 partidos.

Lo que corregí fue la conexión con el menú: al principio, después de simular no se calculaba nada, porque el `if` de simular en `main.cpp` estaba vacío. Agregué ahí `calcularTabla` y `llenarMatriz`, para que la tabla y la matriz se calculen **una sola vez**, justo al simular, como pide la guía.

## 6. Pruebas

Todas las pruebas se hicieron con el programa completo, compilado con `g++ -Wall -Wextra -std=c++17`, sin errores ni advertencias.

| # | Qué probaste | Entrada | Resultado esperado | Resultado obtenido |
| --- | --- | --- | --- | --- |
| 1 | Simular sin equipos | Opción 3 sin registrar | Rechazo, hay 0 | `Rechazado: se necesitan 6 equipos para simular y hay 0.` ✔ |
| 2 | Simular con 5 equipos (límite) | 5 equipos y opción 3 | Rechazo, hay 5 | `Rechazado: ... y hay 5.` ✔ |
| 3 | Resultados antes de simular | Opción 4 | Rechazo | `Reporte no disponible: primero hay que simular el torneo.` ✔ |
| 4 | Modos que no existen | 0, 3 y -1 | Rechazo y volver a preguntar | `Modo no valido. Escribe 1 o 2.` tres veces y vuelve a preguntar ✔ |
| 5 | Modo con texto o decimal | `abc` y `2.5` | Rechazo y volver a preguntar | `Entrada no valida. Escribe un numero entero.` dos veces ✔ |
| 6 | Modo de prueba | 6 equipos, opción 3, modo 2, opción 4 | Los 15 marcadores del ejemplo, en el mismo orden y formato | Reporte idéntico al de `PROYECTO.md`, carácter por carácter ✔ |
| 7 | Simular dos veces | Opción 3 después de simular | Rechazo | `Rechazado: el torneo ya se simulo. Solo se simula una vez por ejecucion.` ✔ |
| 8 | Nombre de 15 letras (límite) | Equipo `Abcdefghijklmno` | La columna MARCADOR no se mueve | `1   Abcdefghijklmno  3 - 3     Halcones`, alineado ✔ |
| 9 | Rango del modo aleatorio | 2000 simulaciones en modo 1 | Siempre 15 partidos y goles entre 0 y 5 | Siempre 15 partidos, mínimo 0, máximo 5, aparecen los 6 valores ✔ |
| 10 | Corridas aleatorias distintas | Dos ejecuciones en modo 1 | Marcadores diferentes | Primeros partidos: `2-5 3-3 0-5` y `1-2 3-2 5-3` ✔ |

## 7. Bitácora de dudas y errores

| # | Duda o error | Cómo lo resolví |
| --- | --- | --- |
| 1 | El archivo no compilaba: había escrito `#include <isotream>` y `#include <isomainp>`. Después volví a escribir mal `<isomanip>`. | Corregí los nombres a `<iostream>` e `<iomanip>`. Aprendí a compilar después de cada cambio para encontrar estos errores rápido. |
| 2 | ¿Por qué hay que incluir `escenario_prueba.h` en mi módulo? | Ahí está la matriz `GOLES_PRUEBA` con los 15 marcadores del modo de prueba. Sin el include, el compilador marca que `GOLES_PRUEBA` no está declarada. Va en mi módulo y no en `torneo.h` porque soy el único que la usa, y ese archivo no se modifica. |
| 3 | Después de simular, la tabla y la matriz salían vacías. | El `if (simularTorneo(...))` en `main.cpp` estaba vacío. Agregué `calcularTabla` y `llenarMatriz` adentro, para que se calculen una sola vez y solo si la simulación fue exitosa. |
| 4 | ¿Cómo hacer que `setw` trate el marcador `3 - 1` como un solo dato? | Lo armo primero como texto con `to_string` en la función `textoMarcador`, y después le aplico `setw(ANCHO_MARCADOR)`. |
| 5 | El profesor pidió usar arreglos y apuntadores en `main`. | Pasamos el `switch` a la función `ejecutarOpcion`, que recibe `Equipo*`, `Partido*`, `int*` y `bool*`. `main` le manda las direcciones con `&` y la función usa `*` para leer o modificar los valores originales. |

## 8. Reflexión

**¿Qué aprendiste?**

Aprendí a usar ciclos anidados para formar todas las parejas de equipos sin repetir y sin que un equipo juegue contra sí mismo, empezando el ciclo de adentro en `local + 1`. También entendí la diferencia entre pasar un dato por valor, por referencia o como `const`: solo uso referencia cuando la función tiene que cambiar el dato original. Por último, practiqué cómo un arreglo se pasa como apuntador a su primer elemento, y cómo con `&` y `*` una función puede modificar las variables de `main`.

**¿Qué cambiarías de tu proceso?**

Compilaría después de cada cambio pequeño. Los errores de los includes se hubieran detectado de inmediato. También acordaría con el equipo desde el principio cómo se iba a armar `main.cpp` y en qué orden se subía cada parte, porque al editar el mismo archivo varias personas tuvimos que reorganizar partes que ya estaban subidas.
