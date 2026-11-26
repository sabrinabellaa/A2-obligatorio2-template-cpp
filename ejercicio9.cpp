#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

// Devuelve la máxima cantidad de likes desde la ronda "ronda" hasta el final, sabiendo que
// A va ganando por "ventaja" goles y si el Pato bailó en el tiro anterior (bailoAntes = 1) o no (0).
// memo[ronda][ventaja][bailoAntes] guarda los resultados ya calculados (-1 = todavía no calculado).
int maxLikesRec(int ronda, int ventaja, int bailoAntes, int k, int *pateadoresA, int *likes, int ***memo) {
    // caso base: ya se patearon las k rondas, no hay más likes para sumar
    if(ronda == k) {
        return 0;
    }

    // si este estado ya se calculó, se devuelve sin recalcular
    if(memo[ronda][ventaja][bailoAntes] != -1) {
        return memo[ronda][ventaja][bailoAntes];
    }

    // patea A: si convierte, la ventaja sube en 1
    int ventajaDespuesDeA = ventaja + pateadoresA[ronda];

    // opción 1: no bailar. El Pato ataja, la ventaja no cambia y el próximo baile no va seguido
    int noBailar = maxLikesRec(ronda + 1, ventajaDespuesDeA, 0, k, pateadoresA, likes, memo);

    if(ventajaDespuesDeA == 0) {
        // no puede bailar: van empatados y si B convierte A queda abajo
        memo[ronda][ventaja][bailoAntes] = noBailar;
    } else {
        // opción 2: bailar. B convierte y la ventaja baja en 1
        int likesBaile = likes[ronda];
        if(bailoAntes == 1) {
            likesBaile = likes[ronda] / 2; // baile seguido: la mitad, redondeado para abajo
        }
        int bailar = likesBaile + maxLikesRec(ronda + 1, ventajaDespuesDeA - 1, 1, k, pateadoresA, likes, memo);
        if(bailar > noBailar) {
            memo[ronda][ventaja][bailoAntes] = bailar;
        } else {
            memo[ronda][ventaja][bailoAntes] = noBailar;
        }
    }

    return memo[ronda][ventaja][bailoAntes];
}

int maxLikes(int k, int *pateadoresA, int *likes) {
     // tabla de memoización: [ronda][ventaja][bailoAntes]
    // ronda de 0 a k, ventaja de 0 a k (como mucho A mete k goles), bailoAntes 0 o 1
    // -> (k+1) * (k+1) * 2 lugares = O(K²) de espacio
    int ***memo = new int**[k+1];
    for(int r=0; r<=k; r++) {
        memo[r] = new int*[k+1];
        for(int v=0; v<=k; v++) {
            memo[r][v] = new int[2];
            memo[r][v][0] = -1; // -1 y no 0, porque 0 likes es un resultado válido
            memo[r][v][1] = -1;
        }
    }

    // arranca en la ronda 0, empatados y sin baile previo
    int resultado = maxLikesRec(0, 0, 0, k, pateadoresA, likes, memo);

    // se libera en orden inverso: primero los arreglos de adentro
    for(int r=0; r<=k; r++) {
        for(int v=0; v<=k; v++) {
            delete[] memo[r][v];
        }
        delete[] memo[r];
    }
    delete[] memo;

    return resultado;
}
int main()
{
    int k;
    cin >> k;

    int *pateadoresA = new int[k];
    for(int i=0; i<k; i++) {
        cin >> pateadoresA[i];
    }

    int *likes = new int[k];
    for(int i=0; i<k; i++) {
        cin >> likes[i];
    }

    int resultado = maxLikes(k, pateadoresA, likes);
    cout << resultado << endl;

    delete[] pateadoresA;
    delete[] likes;
    return 0;

}