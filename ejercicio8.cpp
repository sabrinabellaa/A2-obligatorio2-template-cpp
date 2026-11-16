#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int n, w;
    cin >> n >> w;

    int* limites =  new int[4];
    for(int i=0, i<4, i++) {
        cin >> limites[i];
    }

    int* peso = new int[n];
    int* satisfaccion = new int[n];
    int* categoria = new int[n];
    for(int i=0; i<n; i++) {
        cin >> peso[i] >> satisfaccion[i] >> categoria[i];
    }

    int maxSatTotal = asado(n, w, limites, peso, satisfaccion, categoria);
    cout << maxSatTotal << endl;

    delete[] limites;
    delete[] peso;
    delete[] satisfaccion;
    delete[] categoria;

    return 0;
}