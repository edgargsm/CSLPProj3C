#include <string>
#include <iostream>
#include <fstream> 
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
        
    }
    
    ~Bitstream();

    int readBit(){
        if (this->access.compare("read")!=0){
            cout << "Não foi possivel ler bit porque o acesso ao ficheiro foi de escrita\n";
            return NULL;
        }

        if (this->count < 0){
            char c;
            this->file.read(&(c),1);
            this->byte = reinterpret_cast<unsigned char&>(c);
            
            if (!this->byte){
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

};

Bitstream::~Bitstream()
{
}
