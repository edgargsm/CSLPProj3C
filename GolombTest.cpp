#include <iostream>
#include <vector>
#include "Golomb.h"
using namespace std;

int main() {

    Golomb golomb(5);

    golomb.encode(1);
    golomb.encode(2);
    golomb.encode(3);
    golomb.encode(4);
    golomb.encode(5);
    golomb.encode(6);
    golomb.encode(7);

    vector<int> v= {1,0,0,1,0}; //Numero 4
    cout << golomb.decode(v) << '\n';



}