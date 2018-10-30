#include "converter.hpp"

std::string BinDecConverter::dec2bin(int decimal){
    std::string temp;
    std::string resultado;
    while(decimal > 1){
        int resto = decimal % 2;
        temp += '0' + resto;
        decimal = decimal / 2; 
    }
    temp += '0' + decimal;
    temp.append(8 - temp.size(), '0');

    for(int i = temp.size()-1; i >= 0; i--){
        resultado += temp[i];
    }

    return resultado;
}

unsigned int BinDecConverter::bin2dec(std::string binary){

    int resultado = 0;
    for(unsigned int i = 0; i < binary.size(); i++){
        resultado += (binary[i] - '0')*pow(2, binary.size() - i - 1);
    }
    return resultado;
}