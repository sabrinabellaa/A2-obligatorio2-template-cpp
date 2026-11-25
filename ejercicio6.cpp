#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// devuelve un arreglo con el cartel óptimo y deja en cantPlacas cuántas placas tiene
int* capicua(int* placas, int n, int &cantPlacas) {
    int* frecuencia = new int[1001]();

    // cuenta cuántas placas hay de cada número. O(N)
    for(int i=0; i<n; i++) {
        int nro = placas[i];
        frecuencia[nro]++;
    }

    int* ret = new int[n];

    int k = 0; // próxima posición libre de ret (y al final, el largo del cartel)

    // para la mitad izquierda
    // recorre de 1000 a 0 para que los números más grandes queden primero (cartel lexicográficamente mayor) 
    // O(1001 + N) = O(N)
    for(int i=1000; i>=0; i--) {
       int cantidad = frecuencia[i];
        for(int p=0; p<cantidad/2; p++) { // cantidad/2 = cantidad de pares (con 0 o 1 placa da 0 y no se agrega)
            ret[k++] = i;
        }
    }
    
    int largoMitad = k;

    // recorre de 1000 a 0 y el primer número con cantidad impar (le sobró una placa sin par) es el centro  
    for(int i=1000; i>=0; i--) {
        if(frecuencia[i]%2 == 1) {
            ret[k++] = i;
            break;
        }
    }

    // copia la mitad izquierda al revés para armar la parte derecha
    for(int i=largoMitad-1; i>=0; i--) {
        ret[k++] = ret[i]; 
    }

    cantPlacas = k;
    delete[] frecuencia;
    return ret;
}

int main() {
    int n;
    cin >> n;

    int* placas = new int[n];
    for(int i=0; i<n; i++) {
        cin >> placas[i];
    }

    int cantFinal = 0;

    int* cartel = capicua(placas, n, cantFinal);

    for(int i=0; i<cantFinal; i++) {
        if(i>0) {
            cout << " ";
        }
        cout << cartel[i];
    }

    cout << endl;

    delete[] placas;
    delete[] cartel;
    return 0;
}