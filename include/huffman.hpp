#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <cstring>
#include "huffTree.hpp"
#include "converter.hpp"

/*
 * ====================================================================================================
 *  Classe do algoritmo de Huffman
 * ====================================================================================================  
 */
class Huffman{
    private:
        /*
         * ====================================================================================================
         *  Classe contendo método de ordenação da priority queue
         * ====================================================================================================  
         */
        class Comparable{
            public:
                /*
                 * ====================================================================================================
                 * Método         : operator()
                 * ----------------------------------------------------------------------------------------------------
                 * Descrição      : Lê o arquivo de entrada e preenche o mapa de frequencias
                 * 
                 * Parâmetros
                 *      Node1     : Ponteiro para um nó a ser comparado
                 *      Node2     : Ponteiro para outro nó a ser comparado
                 * 
                 * Retorno        : Retorna um boolean verificando se o primeiro nó é maior que o segundo
                 * 
                 * ====================================================================================================
                 */
                bool operator()(Node *, Node *);
        };
        
        /*
         * ====================================================================================================
         * Atributos da classe
         * ----------------------------------------------------------------------------------------------------
         * 
         * hufftree       : Ponteiro para nó raiz da árvore de Huffman
         * inFileName     : Nome do arquivo de entrada
         * outFileName    : Nome do arquivo de saída
         * inFile         : Arquivo de entrada
         * outFile        : Arquivo de saída
         * frequencies    : Mapa de frequencias dos caracteres Formato: Caractere - Frequencia
         * mapIterator    : Iterator de 'frequencies'
         * codes          : Mapa de novos códigos gerados para cada caractere
         * converter      : Objeto da classe converter, usado para conversões binário <--> decimal
         * 
         * ====================================================================================================
         */
        Node *huffTree;
        std::string inFileName;
        std::string outFileName;
        std::fstream inFile;
        std::fstream outFile;
        std::map<char,int> frequencies;
        std::map<char,int>::iterator mapIterator;
        std::map<char,std::string> codes;
        std::priority_queue<Node *, std::vector<Node *>, Comparable> ordFrequencies;
        BinDecConverter *converter;

        /*
         * ====================================================================================================
         * Método         : fillFrequencies
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Lê o arquivo a ser comprimido e preenche o mapa de frequencias
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        void fillFrequencies();

        /*
         * ====================================================================================================
         * Método         : fillQueue
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : A partir do mapa de frequências preenche a priority queue
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         *      
         * ====================================================================================================
         */
        void fillQueue();

        /*
         * ====================================================================================================
         * Método         : buildTree
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Lê a priority queue e cria a árvore de Huffman
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        void buildTree();
        void printTree(); //Debug only

        /*
         * ====================================================================================================
         * Método         : codify
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Percorre a árvore e preenche o mapa de novos códigos para cada caractere
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        void codify();

        /*
         * ====================================================================================================
         * Método         : fillFrequencies
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Lê o arquivo a ser descomprimido, verifica se o arquivo é válido, preenche o 
         *                  mapa de frequencias e verifica o padding do arquivo comprimido.
         * 
         * Parâmetros
         * 
         * Retorno        : Retorna o padding do arquivo comprimido
         * 
         * ====================================================================================================
         */
        int readHeader();

    public:
        /*
         * ====================================================================================================
         * Método         : Huffman
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Construtor da classe Huffman
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        Huffman();

        /*
         * ====================================================================================================
         * Método         : Huffman
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Destrutor da classe Huffman
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        ~Huffman();

        /*
         * ====================================================================================================
         * Método           : setInFile
         * ----------------------------------------------------------------------------------------------------
         * Descrição        : Seta o inFileName
         * 
         * Parâmetros
         *      inFileName  : Nome do arquivo de entrada 
         * 
         * Retorno          : Vazio
         * 
         * ====================================================================================================
         */
        void setInFile(std::string);

        /*
         * ====================================================================================================
         * Método           : setOutFile
         * ----------------------------------------------------------------------------------------------------
         * Descrição        : Seta o outFileName
         * 
         * Parâmetros
         *      outFileName : Nome do arquivo de saida 
         * 
         * Retorno          : Vazio
         * 
         * ====================================================================================================
         */
        void setOutFile(std::string);
        
        /*
         * ====================================================================================================
         * Método         : compress
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Comprime o arquivo de entrada
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        void compress();
        
        /*
         * ====================================================================================================
         * Método         : decompress
         * ----------------------------------------------------------------------------------------------------
         * Descrição      : Seta o inFileName
         * 
         * Parâmetros
         * 
         * Retorno        : Vazio
         * 
         * ====================================================================================================
         */
        void decompress();


        void print(); //Debug only
};

#endif