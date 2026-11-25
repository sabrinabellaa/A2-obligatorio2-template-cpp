# Bitácora — Obligatorio 2

**Integrantes:** Sabrina Bella (326445), Lara Regen (289762)

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
- 15:00 - 16:00 Releímos las correcciones del obligatorio anterior, leímos las reglas sobre el uso de IA y se las pasamos a Claude Code. Luego leímos la letra del ejercicio 7 y decidimos que lo primero que íbamos a programar era el main.
Escribimos el main y declaramos la función `long long remontadasEpicas(int* llegada, int inicio, int fin);`. Usamos long long porque la letra dice que la cantidad de remontadas épicas puede superar el rango de un entero de 32 bits.
Primera Idea: usar el merge sort de la diapositiva y contar las remontadas entre la mitad izquierda y la derecha antes de intercalar, con dos punteros porque las dos mitades ya están ordenadas. Contamos aparte y no dentro del intercalado porque la condición de remontada (> 2·x) no es la misma que la del orden.

## 2026-11-12 — En conjunto
- 10:00 - 12:00 Hicimos el resto del ejercicio 7, a l merge sort visto en clase le agregamos el conteo con dos punteros antes de intercalar, pasamos los tamaños de cada mitad por parámetro (con un puntero sizeof no sirve para saber el tamaño), cuenta por referencia para acumular en todas las llamadas, y delete de las mitades ya intercaladas para que el espacio quede en O(N). También cambiamos en el main que el array de llegada empiece a llenarse desde 0 en vez del 1 y tenga n lugares en vez de n+1. 
Bug: nos habíamos olvidado del & en `int* intercalar(int *arr1, int n1, int *arr2, int n2, long long& cuenta);` y cuenta nunca se actualizaba. Lo corregimos, volvimos a probar y dio todo bien.
- 13:00 - 14:00 Leímos la letra del ejercicio 6, pensamos el plan de como lo vamos a implementar e hicimos el main. 
Primera Idea: contar cuántas placas hay de cada número y armar la mitad izquierda con los pares de mayor a menor (greedy, para que quede lexicográficamente mayor), poner en el centro el número más grande con cantidad impar y espejar la mitad.

## 2026-11-13 — En conjunto
- 19:00 - 20:45 Empezamos haciendo la función capicua, contando cuántas placas hay de cada número con un arreglo de frecuencias de tamaño 1001, ya que los valores van de 0 a 1000. 
Cuando le pedimos a Claude que lo pruebe nos dieron un par de errores, Bugs: 
Faltaba el return en la función capicua y el programa se caía, el for de la mitad izquierda arrancaba en 1001 con i++ y se salía del arreglo. Lo cambiamos a i=1000 con i--. Además quedaba un espacio al final de la salida, por lo que en el main cambiamos la impresión para poner el espacio antes de cada número salvo el primero. Al hacerlo metimos el número adentro del if y se salteaba el primero, así que lo corregimos dejando solo el espacio en el if. También le pusimos comentarios al ejercicio 7.  
Probamos el 6 de nuevo y nos dimos cuenta que sin querer hicimos un for anidado en el main, lo arreglamos y por ultimo le volvimos a pedir que lo pruebe a Claude y compiló todo bien.

## 2026-11-16 — En conjunto
- 12:30 - 13:45 Decidimos seguir con el ejercicio 8, leímos bien la letra, y usando lo que dimos en clase y las diapositivas de aulas, decidimos de que manera vamos a implementarlo. Comenzamos haciendo el main, e declarando la función asado(n, w, limites, peso, satisfaccion, categoria); 
Primera idea: resolverlo como la mochila 0/1 vista en clase, con una tabla de dos dimensiones (producto y peso) y la recurrencia de tomar o no tomar cada producto.
Agregamos también explciitamente cuales fueron las ideas del ejercicio 6 y 7.

## 2026-11-22 — En conjunto
- 11:00 - 13:30 Esta idea que habíamos pensado no sirve porque esa tabla solo guarda la mejor satisfacción para cada peso, y no cuántos productos de cada categoría se usaron. Al decidir si tomar un producto no hay forma de saber si ya se llegó al máximo de su categoría. Por ejemplo, en el Input 2 la mochila clásica tomaría las tres bebidas (satisfacción 24), cuando solo se permite una. Por eso hay que agregar a la tabla una dimensión por cada categoría, con cuántos productos de esa categoría se llevan usados (de 0 a Lc). Así la tabla queda de N, W, L0, L1, L2, L3, que coincide con el orden que pide la letra.
Con esa idea, implementamos la función asado, la tabla de 6 dimensiones guardada en un arreglo de una dimensión (con una función pos que calcula la posición) y la recurrencia de comprar o no comprar cada producto, controlando el peso y el cupo de su categoría. Revisamos el código y lo probamos con Claude, y dan bien los 4 ejemplos de la letra. En el peor caso la tabla ocupa unos 100 MB, que es lo que pide el orden espacial.
13:35 - 13:45 Leímos el ejercicio 9 y 10 para ya familiarizarnos con ellos y decidir cual haríamos primero. Decidimos que primero haremos el 9.

## 2026-11-25 — En conjunto
- 15:00 - 15:20 Nos fijamos nuevamente si el 8 compilaba y vimos que tenía un error, en el for que rellena el array limites habíamos puesto , en vez de ;. Lo arreglamos, probamos de vuelta y compila.
Empezamos con el ejercicio 9, escribimos el main, y en él declaramos la función `maxLikes(int k, int *pateadoresA, int *likes);` que haremos con memoización.