#include <iostream>
#include "Bitstream.h"
using namespace std;

int main() {

    Bitstream bitstream1("bitTest.txt", "write");
    bitstream1.readBit();
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.writeBit(1);
    bitstream1.writeBit(0);
    bitstream1.endWrite();

    Bitstream bitstream("bitTest.txt", "read");
    bitstream.writeBit(1);
    cout << bitstream.readBit();
    int * arr = bitstream.readBits(7);
    for (int n=0;n<7; n++){
        cout << arr[n];    
    }
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << bitstream.readBit();
    cout << "\n";
    bitstream.readBit();

}