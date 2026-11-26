#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// devuelve la letra de la palabra en esa columna (columna 0 = la última letra), o ' ' si la palabra es más corta
char letraEn(string palabra, int col) {
    if(col >= (int)palabra.length()) {
        return ' ';
    }
    return palabra[palabra.length() - 1 - col];
}

// número que forma la palabra con los dígitos asignados (long long: 10 cifras no entran en un int)
long long valorPalabra(string palabra, int* valor) {
    long long num = 0;
    for(int i=0; i<(int)palabra.length(); i++) {
        num = num * 10 + valor[palabra[i] - 'A'];
    }
    return num;
}

// se terminaron las columnas del resultado
bool esSolucion(int col, int largoRes) {
    return col == largoRes;
}

// el dígito no lo usa otra letra y no es un 0 al principio de una palabra de más de una letra
bool puedoAplicarMovimiento(char letra, int d, bool* usado, bool* noCero) {
    return !usado[d] && !(d == 0 && noCero[letra - 'A']);
}

void aplicarMovimiento(char letra, int d, int* valor, bool* usado) {
    valor[letra - 'A'] = d;
    usado[d] = true;
}

void deshacerMovimiento(char letra, int* valor, bool* usado) {
    usado[valor[letra - 'A']] = false;
    valor[letra - 'A'] = -1;
}

// cand y mejor: [0] = resultado, [1..K] = sumandos. Gana el menor resultado; si empatan, el menor primer sumando, y así.
bool esMejorSolucion(long long* cand, long long* mejor, int K) {
    for(int i=0; i<=K; i++) {
        if(cand[i] != mejor[i]) {
            return cand[i] < mejor[i];
        }
    }
    return false; // son iguales
}

// PODA: estamos en la casilla del resultado y la columna no puede cerrar.
// El dígito del resultado queda obligado a (suma de la columna + acarreo) % 10.
// Si la letra ya tiene otro dígito, o ese dígito no se le puede asignar, ninguna
// asignación de las columnas siguientes puede arreglarlo, así que se corta la rama.
bool puedoPodar(string* palabras, int K, int col, int fila, int acarreo, int sumaCol, int* valor, bool* usado, bool* noCero) {
    if(fila != K || col >= (int)palabras[K].length()) {
        return false; // solo se poda en la casilla del resultado
    }
    int digito = (sumaCol + acarreo) % 10;
    char letra = letraEn(palabras[K], col);
    if(valor[letra - 'A'] != -1) {
        return valor[letra - 'A'] != digito;
    }
    return !puedoAplicarMovimiento(letra, digito, usado, noCero);
}

// recorre la suma casilla por casilla: columna por columna desde las unidades, y en cada columna los sumandos de arriba hacia abajo y al final el resultado
void bt(string* palabras, int K, int col, int fila, int acarreo, int sumaCol, int* valor, bool* usado, bool* noCero, long long* mejor, bool& hayMejor) {
    if(!puedoPodar(palabras, K, col, fila, acarreo, sumaCol, valor, usado, noCero)) {
        if(esSolucion(col, palabras[K].length())) {
            // solo es solución si no sobra acarreo
            if(acarreo == 0) {
                long long* cand = new long long[K + 1];
                cand[0] = valorPalabra(palabras[K], valor);
                for(int i=0; i<K; i++) {
                    cand[i + 1] = valorPalabra(palabras[i], valor);
                }
                if(!hayMejor || esMejorSolucion(cand, mejor, K)) {
                    for(int i=0; i<=K; i++) {
                        mejor[i] = cand[i];
                    }
                    hayMejor = true;
                }
                delete[] cand;
            }
        } else if(fila < K) {
            // casilla de un sumando
            char letra = letraEn(palabras[fila], col);
            if(letra == ' ') {
                // la palabra es más corta: no tiene letra en esta columna
                bt(palabras, K, col, fila + 1, acarreo, sumaCol, valor, usado, noCero, mejor, hayMejor);
            } else if(valor[letra - 'A'] != -1) {
                // la letra ya tiene dígito: solo se suma
                bt(palabras, K, col, fila + 1, acarreo, sumaCol + valor[letra - 'A'], valor, usado, noCero, mejor, hayMejor);
            } else {
                // la letra no tiene dígito: se prueban del 0 al 9
                for(int d=0; d<=9; d++) {
                    if(puedoAplicarMovimiento(letra, d, usado, noCero)) {
                        aplicarMovimiento(letra, d, valor, usado);
                        bt(palabras, K, col, fila + 1, acarreo, sumaCol + d, valor, usado, noCero, mejor, hayMejor);
                        deshacerMovimiento(letra, valor, usado);
                    }
                }
            }
        } else {
            // casilla del resultado: como no se podó, el dígito calculado es válido
            int total = sumaCol + acarreo;
            int digito = total % 10;
            int nuevoAcarreo = total / 10;
            char letra = letraEn(palabras[K], col);
            if(valor[letra - 'A'] != -1) {
                // ya tenía ese mismo dígito: se sigue con la próxima columna
                bt(palabras, K, col + 1, 0, nuevoAcarreo, 0, valor, usado, noCero, mejor, hayMejor);
            } else {
                aplicarMovimiento(letra, digito, valor, usado);
                bt(palabras, K, col + 1, 0, nuevoAcarreo, 0, valor, usado, noCero, mejor, hayMejor);
                deshacerMovimiento(letra, valor, usado);
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;

    for(int t=0; t<T; t++) {
        int K;
        cin >> K;

        // palabras[0..K-1] = sumandos, palabras[K] = resultado
        string* palabras = new string[K + 1];
        for(int i=0; i<=K; i++) {
            cin >> palabras[i];
        }

        int* valor = new int[26];      // dígito de cada letra (A=0 ... Z=25), -1 = sin asignar
        bool* noCero = new bool[26];   // true si es primera letra de una palabra de más de una letra
        for(int i=0; i<26; i++) {
            valor[i] = -1;
            noCero[i] = false;
        }
        bool* usado = new bool[10]();  // dígitos ya tomados por alguna letra

        for(int i=0; i<=K; i++) {
            if(palabras[i].length() > 1) {
                noCero[palabras[i][0] - 'A'] = true;
            }
        }

        // poda por largos, antes del backtracking
        int largoRes = palabras[K].length();
        int largoMax = 0; // largo del sumando más largo
        for(int i=0; i<K; i++) {
            if((int)palabras[i].length() > largoMax) {
                largoMax = palabras[i].length();
            }
        }
        bool posible = largoMax <= largoRes && largoRes <= largoMax + 1;

        // mejor[0] = resultado, mejor[1..K] = sumandos de la mejor solución encontrada
        long long* mejor = new long long[K + 1];
        bool hayMejor = false;

        if(posible) {
            bt(palabras, K, 0, 0, 0, 0, valor, usado, noCero, mejor, hayMejor);
        }

        if(!hayMejor) {
            cout << "imposible" << endl;
        } else {
            for(int i=1; i<=K; i++) {
                if(i > 1) {
                    cout << " + ";
                }
                cout << mejor[i];
            }
            cout << " = " << mejor[0] << endl;
        }

        delete[] palabras;
        delete[] valor;
        delete[] noCero;
        delete[] usado;
        delete[] mejor;
    }

    return 0;
}