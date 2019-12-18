#include <string>
#include <iostream>
#include <fstream> 
#include "Bitstream.h"
#include <math.h>
using namespace std;

class Golomb
{
private:
    int m;
    int b;
    int l;
    Bitstream* bitstream;

    int* binaryRepresentation(int n, int * bin_num){
        //static int bin_num [this->b];

        int i = this->b-1;
        while (n>0){
            bin_num[i] = n %2;
            n = n/2;
            i--;
        }
        

        return bin_num;
    }
public:
    Golomb(int m, Bitstream* bits = NULL)
    {
        this->m = m;
        this->bitstream = bits;
        this->b = ceil(log2(m));
    }

    void encode(int n){
        if (n<0)
            n=(-2*n);
        else if (n>0)
            n = 2*n-1;

        int q = int(floor(n/this->m));
        int r = (n % this->m);

        int binary[this->b]; 
        for (int n=0;n<this->b; n++){
                binary[n]=0;    
            }
        this->binaryRepresentation(r, binary);
        if (this->bitstream==NULL){
            for (int n=0;n<q; n++){
                cout << 1;    
            }
            cout << 0;
            for (int n=0;n<this->b; n++){
                cout << binary[n];
            }
            cout << '\n';
            return;
        }
        for (int n=0;n<q; n++){
            this->bitstream->writeBit(1);    
        }
        this->bitstream->writeBit(0);
        for (int n=0;n<this->l; n++){
            this->bitstream->writeBit(binary[n]);    
        }
    }

    int decode(int * n){
        int q = 0;
        int i = 0;

        while (i<(sizeof(n)/sizeof(int)) && n[i]!=0){
            q++;
            i++;
        }
        cout<<q;
        cout<<"\n";
        cout << (sizeof(n)/sizeof(int));
        cout<<"\n";
        i++;
        int r = 0;
        for (int p =(sizeof(n)/sizeof(int))-1; p>=i; p--){
            r= r + pow(2,-1*(p+1-(sizeof(n)/sizeof(int))))*n[p];
        }
        cout<<r;
        cout<<"\n";
        int num = r+q*this->m;

        if (num%2==0)
            num =(-2*num);
        else if (n>0)
            num = 2*num-1;
        cout << num;
        cout << "\n";
        return num;
    }



    ~Golomb();
};


Golomb::~Golomb()
{
}
