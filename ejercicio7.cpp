#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int* intercalar(int *arr1, int n1, int *arr2, int n2, long long& cuenta) {
    int j = 0;
    for (int i = 0; i < n1; i++) {
        while (j < n2 && arr1[i] > 2 * arr2[j]) {
            j++;
        }
        cuenta += j; 
    }

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
    while (i < n1) {
        ret[k++] = arr1[i++];
    }
    while (j < n2) {
        ret[k++] = arr2[j++];
    }
    return ret;
}

int* mergeSort(int *llegada, int inicio, int fin, long long& cuenta) {
    if (inicio == fin) {
        int* ret = new int[1];
        ret[0] = llegada[inicio];
        return ret;
    }

    int mitad = (inicio + fin) / 2;

    int* ord1 = mergeSort(llegada, inicio, mitad, cuenta);
    int* ord2 = mergeSort(llegada, mitad + 1, fin, cuenta);

    int* ret = intercalar(ord1, mitad - inicio + 1, ord2, fin - mitad, cuenta);
    delete[] ord1; 
    delete[] ord2;
    return ret;
}

long long remontadasEpicas( int* llegada, int inicio, int fin) {
    long long cuenta = 0;
    int *ordenado = mergeSort(llegada, inicio, fin, cuenta);
    delete[] ordenado;
    return cuenta;
}

int main() {
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