#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

void bt(string* palabras, int K, int col, int fila, int acarreo, int sumaCol, int* valor, bool* usado, bool* noCero, long long* mejor, bool& hayMejor) {

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