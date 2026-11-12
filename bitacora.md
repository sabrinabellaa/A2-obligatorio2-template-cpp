# Bitácora — Obligatorio 2

**Integrantes:** Nombre Apellido (Nº estudiante), Nombre Apellido (Nº estudiante)

> **Instrucciones** (borrar esta sección antes de entregar): agregar una entrada por
> cada día trabajado, indicando la fecha y quién trabajó (un integrante o "En conjunto").
> Registrar el proceso real: ideas exploradas, decisiones y su justificación, partes de
> implementaciones, bugs encontrados y cómo se corrigieron, resultados de pruebas y dudas
> abiertas. Si se usó IA ese día, indicar herramienta, consulta y qué se hizo con la
> respuesta. Una bitácora escrita íntegramente el día de la entrega implica pérdida de puntos.

## 2026-11-11 — Nombre
- Ejemplo: Leí la letra del ejercicio 6. Primera idea: ... pero la restricción de
  complejidad pide ..., así que ...

## AAAA-MM-DD — En conjunto
- Ejemplo: Implementamos ... Bug: ... Lo corregimos ...
- Pasan los casos de prueba 1 a 4 del ejercicio 6.

## 2026-11-11 — En conjunto
-  15:00 - 16:00 Releímos las correcciones del obligatorio anterior, leimos las reglas sobre el uso de IA, y se las pasamos a Claude Code. Luego leímos la letra del ejercicio 7 y decidimos que lo primero que vamos a programar es el main. Escribimos el main y declaramos la función long long remontadasEpicas(int* llegada, int inicio, int fin);. long long porque en la letra dice que la cantidad de remontadas épicas puede superar el rango de un entero de 32 bits.

## 2026-11-12 — En conjunto
- 10:00 - 12:00 Hicimos el resto del ejercicio 7, la lógica de merge sort (con intercalar) y cambiamos en el main que el array de llegada empiece a llenarse desde 0 en vez del 1 y tenga n lugares en vez de n-1. Le pedimos a Claude que corra los ejemplos de la letra y vimos que sin querer nos habíamos olvidado de poner el & en int* intercalar(int *arr1, int n1, int *arr2, int n2, long long& cuenta); y nunca se actualizaba cuenta. Lo arreglamos y volvimos a probar, nos dio todo bien. 
- 13:00 - 14:00 Leímos la letra del ejercicio 6, pensamos como lo vamos a implementar e hicimos el main.