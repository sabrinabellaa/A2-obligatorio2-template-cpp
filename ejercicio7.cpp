#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// recibe dos arreglos ordenados (la mitad izquierda y la derecha), suma a cuenta
// las remontadas entre ellas y devuelve un arreglo nuevo
// con los dos intercalados en orden. O(n1 + n2)
int* intercalar(int *arr1, int n1, int *arr2, int n2, long long& cuenta) {

    // cuenta las remontadas: todo lo de arr1 llegó antes que todo lo de arr2
    // como están ordenados, j nunca vuelve para atrás. O(n1 + n2)
    int j = 0; // recorre arr2
    for (int i = 0; i < n1; i++) {
        while (j < n2 && arr1[i] > 2 * arr2[j]) {
            j++;
        }
        cuenta += j; // los j primeros de arr2 cumplen arr1[i] > 2 * arr2[j]
    }

    // junta las dos mitades en un solo arreglo ordenado (merge de clase)
    // el conteo se hace aparte, antes, porque para ordenar se compara con < y para contar con > 2*
    int* ret = new int[n1 + n2];
    int i = 0;
    int k = 0;
    j = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            ret[k++] = arr1[i++];
        } else {
            ret[k++] = arr2[j++];
        }
    }

    // copia lo que haya sobrado de alguna de las dos mitades
    while (i < n1) {
        ret[k++] = arr1[i++];
    }
    while (j < n2) {
        ret[k++] = arr2[j++];
    }
    return ret;
}

// ordena el array de llegada y va sumando en cuenta las remontadas.
int* mergeSort(int *llegada, int inicio, int fin, long long& cuenta) {

    // CB: un solo corredor, no hay remontadas
    if (inicio == fin) {
        int* ret = new int[1];
        ret[0] = llegada[inicio];
        return ret;
    }

    int mitad = (inicio + fin) / 2;

    int* ord1 = mergeSort(llegada, inicio, mitad, cuenta);
    int* ord2 = mergeSort(llegada, mitad + 1, fin, cuenta);

    // n1 = mitad - inicio + 1 y n2 = fin - mitad son los tamaños de cada mitad
    // se pasan por parámetro porque con un puntero no se puede saber el tamaño (sizeof no sirve)
    int* ret = intercalar(ord1, mitad - inicio + 1, ord2, fin - mitad, cuenta);

    delete[] ord1; 
    delete[] ord2;
    return ret;
}

// devuelve la cantidad de remontadas épicas del array de llegadas
long long remontadasEpicas( int* llegada, int inicio, int fin) {
    long long cuenta = 0;
    int *ordenado = mergeSort(llegada, inicio, fin, cuenta);
    delete[] ordenado;
    return cuenta;
}

int main() 
{
    int n;
    cin >> n;

    int* llegada = new int[n];
    for(int i=0; i<n; i++) {
        cin >> llegada[i];
    }

    long long resultado = remontadasEpicas(llegada, 0, n - 1);

    cout << resultado << endl;
    
    delete[] llegada;
    return 0;
}