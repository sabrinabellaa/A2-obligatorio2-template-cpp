#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// La tabla tiene 6 dimensiones: [producto][peso][usados cat 0][cat 1][cat 2][cat 3].
// Se guarda en un arreglo de una dimensión y esta función calcula la posición.
// d0..d3 = tamaño de cada dimensión de categoría (Lc + 1, porque se puede usar de 0 a Lc).
int pos(int i, int w, int a, int b, int c, int d, int W, int d0, int d1, int d2, int d3) {
    return ((((i * (W + 1) + w) * d0 + a) * d1 + b) * d2 + c) * d3 + d;
}

// tabla[i][w][a][b][c][d] = máxima satisfacción usando solo los primeros i productos,
// con peso total <= w y a lo sumo a achuras, b cortes, c bebidas y d vegetales.
int asado(int n, int W, int* limites, int* peso, int* satisfaccion, int* categoria) {
    int d0 = limites[0] + 1;
    int d1 = limites[1] + 1;
    int d2 = limites[2] + 1;
    int d3 = limites[3] + 1;

    // O(N*W*L0*L1*L2*L3) en espacio. El () la inicializa toda en 0:
    // con 0 productos (fila i = 0) la mejor satisfacción es 0 (no comprar nada).
    int* tabla = new int[(n + 1) * (W + 1) * d0 * d1 * d2 * d3]();

    for(int i=1; i<=n; i++) {
        int p = peso[i-1]; // el producto i de la tabla es el i-1 del arreglo
        int s = satisfaccion[i-1];
        int cat = categoria[i-1];

        for(int w=0; w<=W; w++) {
            for(int a=0; a<d0; a++) {
                for(int b=0; b<d1; b++) {
                    for(int c=0; c<d2; c++) {
                        for(int d=0; d<d3; d++) {
                            // opción 1: no comprar el producto i
                            int mejor = tabla[pos(i-1, w, a, b, c, d, W, d0, d1, d2, d3)];

                            // opción 2: comprarlo, si entra en el peso y queda lugar en su categoría
                            int cupo[4] = {a, b, c, d};
                            if(p <= w && cupo[cat] > 0) {
                                cupo[cat]--; // se gasta un lugar de su categoría
                                int conProducto = s + tabla[pos(i-1, w - p, cupo[0], cupo[1], cupo[2], cupo[3], W, d0, d1, d2, d3)];
                                if(conProducto > mejor) {
                                    mejor = conProducto;
                                }
                            }

                            tabla[pos(i, w, a, b, c, d, W, d0, d1, d2, d3)] = mejor;
                        }
                    }
                }
            }
        }
    }

    // la respuesta usa todos los productos, todo el peso y todos los cupos
    int resultado = tabla[pos(n, W, limites[0], limites[1], limites[2], limites[3], W, d0, d1, d2, d3)];
    delete[] tabla;
    return resultado;
}

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