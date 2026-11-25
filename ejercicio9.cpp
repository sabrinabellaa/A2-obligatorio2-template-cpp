#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int maxLikes(int k, int *pateadoresA, int *likes) {
    return 0; 
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