# Bitácora — Obligatorio 2

**Integrantes:** Sabrina Bella (326445), Lara Regen (289762)

## 2026-11-11 — En conjunto
- 15:00 - 16:00 Releímos las correcciones del obligatorio anterior, leímos las reglas sobre el uso de IA y se las pasamos a Claude. Luego leímos la letra del ejercicio 7 y decidimos que lo primero que íbamos a programar era el main.
Escribimos el main y declaramos la función `long long remontadasEpicas(int* llegada, int inicio, int fin);`. Usamos long long porque la letra dice que la cantidad de remontadas épicas puede superar el rango de un entero de 32 bits.
Primera Idea: usar el merge sort de la diapositiva y contar las remontadas entre la mitad izquierda y la derecha antes de intercalar, con dos punteros porque las dos mitades ya están ordenadas. Contamos aparte y no dentro del intercalado porque la condición de remontada (> 2·x) no es la misma que la del orden.

## 2026-11-12 — En conjunto
- 10:00 - 12:00 Hicimos el resto del ejercicio 7, al merge sort visto en clase le agregamos el conteo con dos punteros antes de intercalar, pasamos los tamaños de cada mitad por parámetro (con un puntero sizeof no sirve para saber el tamaño), cuenta por referencia para acumular en todas las llamadas, y delete de las mitades ya intercaladas para que el espacio quede en O(N). También cambiamos en el main que el array de llegada empiece a llenarse desde 0 en vez del 1 y tenga n lugares en vez de n+1. 
Bug: nos habíamos olvidado del & en `int* intercalar(int *arr1, int n1, int *arr2, int n2, long long& cuenta);` y cuenta nunca se actualizaba. Lo corregimos, volvimos a probar y dio todo bien.

## 2026-11-12 — En conjunto
- 13:00 - 14:00 Leímos la letra del ejercicio 6, pensamos el plan de como lo vamos a implementar e hicimos el main. 
Primera Idea: contar cuántas placas hay de cada número y armar la mitad izquierda con los pares de mayor a menor (greedy, para que quede lexicográficamente mayor), poner en el centro el número más grande con cantidad impar y espejar la mitad.

## 2026-11-13 — En conjunto
- 19:00 - 20:45 Empezamos haciendo la función capicua, contando cuántas placas hay de cada número con un arreglo de frecuencias de tamaño 1001, ya que los valores van de 0 a 1000. 
Cuando le pedimos a Claude que lo pruebe nos dieron un par de errores, Bugs: 
Faltaba el return en la función capicua y el programa se caía, el for de la mitad izquierda arrancaba en 1001 con i++ y se salía del arreglo. Lo cambiamos a i=1000 con i--. Además quedaba un espacio al final de la salida, por lo que en el main cambiamos la impresión para poner el espacio antes de cada número salvo el primero. Al hacerlo metimos el número adentro del if y se salteaba el primero, así que lo corregimos dejando solo el espacio en el if. También le pusimos comentarios al ejercicio 7.  
Probamos el 6 de nuevo y nos dimos cuenta que sin querer hicimos un for anidado en el main, lo arreglamos y por último le volvimos a pedir que lo pruebe a Claude y compiló todo bien.

## 2026-11-16 — En conjunto
- 12:30 - 13:45 Decidimos seguir con el ejercicio 8, leímos bien la letra, y usando lo que dimos en clase y las diapositivas de aulas, decidimos de qué manera vamos a implementarlo. Comenzamos haciendo el main, declarando la función asado(n, w, limites, peso, satisfaccion, categoria); 
Primera idea: resolverlo como la mochila 0/1 vista en clase, con una tabla de dos dimensiones (producto y peso) y la recurrencia de tomar o no tomar cada producto.
Agregamos también explícitamente cuales fueron las ideas del ejercicio 6 y 7.

## 2026-11-22 — En conjunto
- 11:00 - 13:30 Esta idea que habíamos pensado no sirve porque esa tabla solo guarda la mejor satisfacción para cada peso, y no cuántos productos de cada categoría se usaron. Al decidir si tomar un producto no hay forma de saber si ya se llegó al máximo de su categoría. Por ejemplo, en el Input 2 la mochila clásica tomaría las tres bebidas (satisfacción 24), cuando solo se permite una. Por eso hay que agregar a la tabla una dimensión por cada categoría, con cuántos productos de esa categoría se llevan usados (de 0 a Lc). Así la tabla queda de N, W, L0, L1, L2, L3, que coincide con el orden que pide la letra.
Con esa idea, implementamos la función asado, la tabla de 6 dimensiones guardada en un arreglo de una dimensión (con una función pos que calcula la posición) y la recurrencia de comprar o no comprar cada producto, controlando el peso y el cupo de su categoría. En el peor caso la tabla ocupa unos 100 MB, que es lo que pide el orden espacial.

## 2026-11-22 — En conjunto
- 13:35 - 13:45 Leímos el ejercicio 9 y 10 para ya familiarizarnos con ellos y decidir cual haríamos primero. Decidimos que primero haremos el 9.

## 2026-11-25 — En conjunto
- 15:00 - 15:20 Nos fijamos nuevamente si el 8 compilaba y vimos que tenía un error, en el for que rellena el array limites habíamos puesto , en vez de ;. Lo arreglamos, probamos de vuelta y compila.
Empezamos con el ejercicio 9, escribimos el main, y en él declaramos la función `maxLikes(int k, int *pateadoresA, int *likes);` que haremos con memoización.

## 2026-11-25 — En conjunto
- 15:20 - 16:00 Realizamos la autoría y la justificación de todos los ejercicios que ya terminamos, el 6, 7 y 8.

## 2026-11-26 — En conjunto
- 5:30 - 7:50 - Primera idea para el ejercicio 9: resolverlo con programación dinámica guardando solo la ronda y si el Pato bailó en el tiro anterior (una tabla de K*2), y en cada tiro de B elegir entre bailar o no bailar.
Pero no se puede porque, sin saber por cuánto va ganando A, no hay forma de controlar que A nunca quede abajo en el marcador: bailar solo es posible si A va ganando en ese momento, y eso depende de todo lo que pasó antes. Por eso agregamos la ventaja al estado, que va de 0 a K. Así la tabla de memoización queda de (K+1) * (K+1) * 2, que es O(K²) como pide la letra.
Idea final: una función recursiva con memoización cuyo estado es (ronda, ventaja, bailó antes). En cada ronda patea primero A y, si convierte, la ventaja sube en 1. Después se elige lo mejor entre no bailar (la ventaja no cambia y el próximo baile no va seguido) y bailar, que solo se puede si A va ganando porque B convierte y la ventaja baja en 1; si el Pato bailó en el tiro anterior, suma la mitad de los likes. Cada estado se guarda en la tabla memo[ronda][ventaja][bailoAntes], inicializada en -1 (y no en 0, porque 0 likes es un resultado válido), así cada uno se calcula una sola vez.

## 2026-11-26 — En conjunto
- 7:50 - 8:15 Le mandamos a Claude nuestras ideas, y nos guió para escribir `maxLikesRec` y `maxLikes` con nuestro diseño. Luego de que terminamos de escribir el código, le pedimos a Claude que las compile y las pruebe con los 5 ejemplos de la letra.
Bugs: dos errores de tipeo que no dejaban compilar (`venrtaja` en vez de `ventaja`, `pateakdoresA` en vez de `pateadoresA`). Los corregimos.
Al probar los ejemplos, el Input 4 daba 100 en vez de 95. El bug era que en la rama de bailar no restábamos 1 a la ventaja al llamar recursivamente, aunque nuestro propio comentario ya decía que la ventaja debía bajar al convertir B. Lo corregimos pasando `ventajaDespuesDeA - 1`, y los 5 ejemplos dieron bien.
También nos faltaba liberar `memo[r]` (el arreglo de punteros intermedio) al borrar la tabla, nos quedaba un leak de memoria. Lo agregamos. Volvimos a probar y está todo bien.

## 2026-11-26 — En conjunto
- 14:00 - 15:40 Leimos la letra del ejercicio 10, usamos Claude para entender bien qué pedía e intentamos hacer el main. Como nos pareció más complejo que los demás, hicimos el main a medias con lo que nos fue pareciendo adecuado para la lógica pero sin la intención de que compile. Luego recurrimos a Claude para que nos ayude a razonar cómo hacer que a partir de nuestras ideas iniciales, pudiéramos completar el main. También declaramos la función `bt`.

## 2026-11-26 — En conjunto
- 16:00 - 19:00 Ya teníamos la base del main escrita y nuestra primera idea era usar el framework de backtracking de optimización visto en clase, porque puede haber varias soluciones y hay que imprimir la de menor resultado, desempatando por los sumandos. Lo que no sabíamos era cómo recorrer las letras para poder podar. Le pasamos a Claude la presentación de backtracking del curso y le pedimos que nos ayude a razonarlo. Nos explicó, con el ejemplo AB + BA = CC paso a paso, que conviene resolver la suma columna por columna desde las unidades, como una suma a mano con acarreo. Así solo se prueban dígitos en las letras de los sumandos: el dígito del resultado queda obligado a (suma de la columna + acarreo) % 10, y si no coincide con el de la letra se puede cortar la rama sin mirar las columnas siguientes. En base a esto, hicimos `bt` y declaramos las funciones auxiliares. Fuimos mostrándole nuestro proceso a Claude y fuimos razonando y mandándole nuestras ideas para que nos ayude a ordenarlas. Por último, programamos las funciones auxiliares. 
En el proceso fueron surgiendo varios errores que corregimos con la ayuda de Claude:
-- Inicialmente nos faltó la función `deshacerMovimiento` después de cada recursión de `aplicarMovimiento`, lo que hacía que las letras queden con dígitos de ramas anteriores y aparece "imposible" donde había solución.
-- Cuando llamamos a `bt`, al parámetro de `sumaCol` no le estábamos pasando 0, si no que `sumaCol`, lo que hacía que las sumas de todas las columnas se vayan arrastrando.
-- En el caso base de `bt` no estábamos chequeando que acarreo == 0 y se aceptaban sumas que se "pasan".
-- `letraEn` retornaba palabra[col] y la palabra se recorría al revés. Lo cambiamos para que retorne palabra[palabra.length() - 1 - col] para que se recorra en orden.
-- Cada vez que usábamos una letra como índice de `valor` o de `noCero` nos faltaba restar 'A' para convertir cada letra en una posición de 0 a 25.
-- `hayMejor` no se pasaba por referencia (&) y no se actualizaba.

## 2026-11-26 — En conjunto
19:15 - 20:00 Compilamos el ejercicio 9 y nos dio todo perfecto. Por otro lado hicimos la revisión de código de todos los ejercicios para asegurarnos que esté todo bien y nos dimos cuenta que utilizamos max y eso no está permitido, por lo que lo cambiamos. 
Por último escribimos las justificaciones de orden y la autoría del ejercicio 9 y 10, arreglamos faltas de ortografía y redacción.

## 2026-11-26 — En conjunto
20:05 - 20:15 También escribimos en `justificacion.md` del ejercicio 10 una explicación de las podas que usa `bt`.