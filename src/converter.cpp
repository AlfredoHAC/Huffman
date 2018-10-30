#include "converter.hpp"

std::string BinDecConverter::dec2bin(int decimal){
    // Variáveis auxiliares
    std::string temp;
    std::string resultado;

    // Efetua as decisões sucessivas e obtém o resto de cada uma
    while(decimal > 1){
        int resto = decimal % 2;
        temp += '0' + resto;
        decimal = decimal / 2; 
    }

    // Obtém o ultimo bit decorrente da ultima divisão
    temp += '0' + decimal;
    
    // Forma um bloco de 8 bits preenchendo os bits faltantes com '0'
    temp.append(8 - temp.size(), '0');

    // Preenche o resultado de forma inversa
    for(int i = temp.size()-1; i >= 0; i--){
        resultado += temp[i];
    }

    return resultado;
}

unsigned int BinDecConverter::bin2dec(std::string binary){
    //Variável auxiliar
    int resultado = 0;

    //Percorre toda a cadeia e multiplica cada bit pela base elevado ao expoente correspondente a sua posição
    for(unsigned int i = 0; i < binary.size(); i++){
        resultado += (binary[i] - '0')*pow(2, binary.size() - i - 1);
    }

    return resultado;
}