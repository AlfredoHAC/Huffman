#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <iostream>
#include <cmath>

/*
 * ====================================================================================================
 *  Classe de conversão binário <--> decimal
 * ====================================================================================================  
 */
class BinDecConverter{
    public:
        /*
         * ====================================================================================================
         * Método         : dec2bin
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Converte um inteiro para seu valor correspondente em binário
         * 
         * Parâmetros
         *      decimal   : Inteiro a ser convertido para binário
         * 
         * Retorno        : Cadeia de bits correspondente ao inteiro
         * 
         * ====================================================================================================
         */
        std::string dec2bin(int);

        /*
         * ====================================================================================================
         * Método         : bin2dec
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Converte uma cadeia de binária para seu inteiro correspondente
         * 
         * Parâmetros
         *      binary    : String contendo a cadeia de bits a ser convertido para inteiro
         * 
         * Retorno        : Inteiro correspondente a cadeia de bits informada
         * 
         * ====================================================================================================
         */
        unsigned int bin2dec(std::string);
};

#endif