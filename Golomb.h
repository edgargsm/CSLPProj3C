#include <string>
#include <iostream>
#include <fstream> 
#include "Bitstream.h"
#include <math.h>
#include <vector>
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
        /*if (n<0)
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
        }*/


        if (n<0)
            n=(-2*n);
        else if (n>0)
            n = 2*n-1;
        
        int r = n % this->m;

        for (int i = 0; i< n / this->m; i++)
            this->bitstream->writeBit(1);
        this->bitstream->writeBit(0);

        this->bitstream->writeBits(r,this->b);
    }

    int decode(vector<int> n){
        /*int q = 0;
        int i = 0;

        while (i<n.size() && n[i]!=0){
            q++;
            i++;
        }
        i++;
        int r = 0;
        for (int p =n.size()-1; p>=i; p--){
            r= r + pow(2,-1*(p+1-n.size()))*n[p];
        }
        int num = r+q*this->m;
        if (num%2==0)
            num =(num/-2);
        else
            num = (num+1)/2;
        return num;*/

        int q = 0;
        while (this->bitstream->readBit() != 0){
            q ++;
        }

        int r=this->bitstream->readBits(this->b);
        int ret = r+q*this->m;
        if (ret%2==0)
            ret = (int)ret/-2;
        
        else
            ret = (ret+1)/2;
        
        return ret;
    }



    ~Golomb();
};


Golomb::~Golomb()
{
}
