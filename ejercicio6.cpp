#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int* placas = new int[n];
    for(int i=0; i<n; i++) {
        cin >> placas[i];
    }

    int* cartel = capicua(placas, n);
    for(int i=0; i<n; i++) {
        cout << cartel[i] << " ";
    }
    return 0;
}