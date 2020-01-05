#include <string>
#include <iostream>
#include <fstream> 
#include <math.h>
using namespace std;

class Bitstream
{
private:
    fstream file;
    string access;
    unsigned char byte;
    int count;
    string first_line;

public:
    Bitstream(string file,string acc,string init_message = "",bool read_FirstLine = false){
        this->file.open(file.c_str());
        this->access = acc;
        this->first_line = "";
        if (acc.compare("write")==0 && init_message.size()==0){
            this->file << init_message.c_str();
        }
        else if (acc.compare("read")==0 && read_FirstLine){
            string s;
            getline (this->file,this->first_line);
        }
        if (acc.compare("write")==0){
            this->count = 7;
            this->byte = 0;
        }
        else if (acc.compare("read")==0){
            this->count = -1;
            this->byte = 0;
        }
        
        
    }
    
    ~Bitstream();


    int readBit(){
        if (this->access.compare("read")!=0){
            cout << "Não foi possivel ler o bit porque o acesso ao ficheiro foi de escrita\n";
            return NULL;
        }

        if (this->count < 0){
            char c;
            this->file.read(&(c),1);
            this->byte = reinterpret_cast<unsigned char&>(c);
            
            if (!this->file.good()){
                cout << "Ficheiro já foi completamente lido.\n";
                this->file.close();
                return NULL;
            }
            this->count = 7;
            }
        
        
        int bit = (this->byte >> this->count) & 1;
        this->count -= 1;

        return bit;
    }


    void writeBit(int bit){
        if (this->access.compare("write")!=0){
            cout << "Não foi possivel escrever o bit porque o acesso ao ficheiro foi de leitura\n";
            return;
        }

        if ((this->count) < 0){

            char c = reinterpret_cast<char&>(this->byte);
            //this->file.write(&(c),1);
            this->file << this->byte;
            this->byte = 0;
            this->count = 7;
        }

        this->byte = this->byte | (bit << this->count);
        this->count --;
    }

    void endWrite(){
        if (this->access.compare("write")!=0){
            cout << "Não foi possivel escrever o bit porque o acesso ao ficheiro foi de leitura\n";
            return;
        }
        
        if (this->count!=7){
            char c = reinterpret_cast<char&>(this->byte);
            this->file << this->byte;
        }
        this->file.close();

        cout << "Escrita de bits finalizada.\n";
    }

    int readBits(int n){


        /*int * arr = new int [n];

        for (int i=0; i<n; i++){
            arr[i] =  this->readBit();
        }

        return arr;*/

        int num = 0;
        for (int i = n-1; i>= 0; i--){

            int bit = this->readBit();
            
            int val = bit << i & (int)pow(2,i);
            num += val;
        }
        return num;
    }

    void writeBits(int n, int nbits){
        
        for (int i = nbits-1; i >= 0; i--){
            this->writeBit( n >> i & 1);
        }
    }


};

Bitstream::~Bitstream()
{
}
