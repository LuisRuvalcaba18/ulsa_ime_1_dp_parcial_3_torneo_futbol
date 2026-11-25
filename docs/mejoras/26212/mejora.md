# Propuesta de mejora

Propuesta de mejora elaborada por: Romeo Ramos Zertuche

**Matrícula:** 26212  
**Título de la propuesta:** Reporte de estadísticas generales del torneo

## 1. Impacto

Es una **mejora**. Hoy, después de simular, el programa muestra los resultados partido por partido, la tabla por equipo, la ficha de un equipo y la matriz, pero no hay un **resumen del torneo completo**.

La mejora agrega un reporte nuevo con:

- Partidos jugados y goles totales del torneo.
- Promedio de goles por partido.
- Cuántos partidos terminaron empatados.
- Cuántos partidos ganó el local y cuántos el visitante.
- El partido con más goles. Si hay empate, se muestran todos, en el orden en que se jugaron.

Beneficia al usuario, que ve de un vistazo cómo fue el torneo, y al equipo, porque sirve para comprobar el cálculo a mano: los goles totales deben ser iguales a la suma de los goles a favor de todos los equipos en la tabla.

Ejemplo con el modo de prueba:

```
--- ESTADISTICAS DEL TORNEO ---
Partidos jugados: 15
Goles totales: 66
Promedio de goles por partido: 4.40
Partidos empatados: 2
Victorias locales: 7
Victorias visitantes: 6
Partido con mas goles: Leones 5 - 3 Pumas (8 goles)
```

## 2. Qué implica en el diseño

- **Registros `Equipo` y `Partido`: no cambian.** Toda la información necesaria ya está en el arreglo de `Partido`: quién jugó y cuántos goles anotó cada uno.
- **Registro nuevo `EstadisticasTorneo`** con `totalGoles`, `partidosEmpatados`, `victoriasLocales`, `victoriasVisitantes` y `maxGolesPartido`. Junta en un solo dato todos los resultados del cálculo, en lugar de manejar cinco variables sueltas.
- **Constantes:** `OPCION_ESTADISTICAS = 9`, y `OPCION_SALIR` pasa de 9 a 10. Se usan constantes con nombre, no números sueltos.
- **Funciones nuevas en `simulacion.h` (módulo 2).** Van ahí porque trabajan sobre el arreglo de partidos que genera ese módulo.
  - `golesDelPartido(partido)`: regresa `golesLocal + golesVisitante`. Evita repetir esa suma en varios lugares.
  - `calcularEstadisticas(partidos, totalPartidos, estadisticas)`: recorre los partidos una vez y llena el registro. Recibe `estadisticas` **por referencia**, porque lo modifica, y los partidos como `const`, porque solo los lee.
  - `mostrarEstadisticas(equipos, partidos, totalPartidos, simulado)`: imprime el reporte. Reutiliza `reporteDisponible`, `imprimirTitulo` y `textoMarcador` de `torneo.h`.
- **Promedio:** se calcula como decimal (`double`) y se imprime con 2 decimales, con `fixed` y `setprecision(2)` de `<iomanip>`.
- **Menú:** se agrega la opción "Mostrar estadisticas del torneo" y un `case` nuevo en `ejecutarOpcion`.
- **Rechazo:** igual que los demás reportes, no funciona antes de simular el torneo.
- **Sin datos guardados de más:** las estadísticas se calculan cada vez que se piden y no se guardan en `main`. Así no pueden quedar desactualizadas, y recorrer 15 partidos es inmediato.

## 3. Receta

```
INICIO
    [CAMBIA] mostrar el menu con la opcion 9 "Mostrar estadisticas del torneo"
             y Salir como opcion 10
    leer opcion
    segun la opcion:
        1 a 8: (pasos existentes)
        [NUEVO] 9: mostrarEstadisticas(equipos, partidos, totalPartidos, torneoSimulado)
        [CAMBIA] 10: salir
        otra: avisar que la opcion no existe
    repetir hasta que la opcion sea Salir
FIN

[NUEVO] golesDelPartido(partido):
    [NUEVO] regresar partido.golesLocal + partido.golesVisitante

[NUEVO] calcularEstadisticas(partidos, totalPartidos, estadisticas por referencia):
    [NUEVO] poner en 0 totalGoles, partidosEmpatados, victoriasLocales,
            victoriasVisitantes y maxGolesPartido
    [NUEVO] para cada partido del arreglo:
        [NUEVO] goles = golesDelPartido(partido)
        [NUEVO] sumar goles a totalGoles
        [NUEVO] si golesLocal == golesVisitante: sumar 1 a partidosEmpatados
        [NUEVO] si no, si golesLocal > golesVisitante: sumar 1 a victoriasLocales
        [NUEVO] si no: sumar 1 a victoriasVisitantes
        [NUEVO] si goles > maxGolesPartido: maxGolesPartido = goles

[NUEVO] mostrarEstadisticas(equipos, partidos, totalPartidos, simulado):
    [NUEVO] si no se ha simulado: avisar "Reporte no disponible" y regresar
    [NUEVO] calcularEstadisticas(partidos, totalPartidos, estadisticas)
    [NUEVO] promedio = totalGoles / totalPartidos, como decimal
    [NUEVO] imprimir el titulo "ESTADISTICAS DEL TORNEO"
    [NUEVO] imprimir partidos jugados, goles totales, promedio con 2 decimales,
            partidos empatados, victorias locales y victorias visitantes
    [NUEVO] para cada partido del arreglo:
        [NUEVO] si golesDelPartido(partido) == maxGolesPartido:
            [NUEVO] imprimir "Partido con mas goles: " local, marcador,
                    visitante y "(maxGolesPartido goles)"
```
