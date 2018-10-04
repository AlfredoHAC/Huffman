#include <iostream>
#include <fstream>
#include <clocale>
#include <unistd.h>
#include "huffman.hpp"
#include "huffTree.hpp"

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");

    if(argc < 2){
        std::cerr << "Uso: ./huff [MODO] [OPÇÃO] ..." << std::endl;
        exit(EXIT_FAILURE);
    }

    Huffman *huff = new Huffman();

    char ch;
    while((ch = getopt(argc, argv, "hc:d:s:o:")) != EOF){
        switch(ch){
            case 'h':
                std::cout << "Implementação do algoritmo de Huffman" << std::endl;
                std::cout << "Uso: ./huff [MODO] <ARQUIVO> [OPÇÃO] ..." << std::endl;
                std::cout << "MODO:" << std::endl;
                std::cout << "  -c <arquivo de entrada> \tComprime o arquivo especificado" << std::endl;
                std::cout << "  -d <arquivo comprimido> \tDescomprime um arquivo já comprimido" << std::endl;
                std::cout << "  -s <arquivo comprimido> \tMostra estatísticas sobre o arquivo comprimido" << std::endl;
                std::cout << std::endl << "OPÇÕES:" << std::endl;
                std::cout << "  -h \t\t\t\t\tMostra esse texto de ajuda" << std::endl;
                std::cout << "  -o <arquivo de saída> \tRedireciona a saída para o arquivo informado" << std::endl;
                std::cout << std::endl;
                break;
            case 'c':
                {
                    std::cout << "Comprimindo..." << std::endl;
                    
                    std::ifstream arquivo(optarg, std::ios_base::in);
                    
                    if(!arquivo.is_open()){
                        std::cerr << "Erro: Arquivo não encontrado" << std::endl;
                        exit(EXIT_FAILURE);
                    }else{
                        std::cout << "Calculando frequências..." << std::endl;
                        huff->fillFrequencies(&arquivo);
                    }
                    
                    std::cout << "Preenchendo fila de prioridades..." << std::endl;
                    huff->fillQueue();

                    std::cout << "Construíndo árvore de Huffman..." << std::endl;
                    huff->buildTree();
                    huff->codify();
                    huff->printTree();

                }
                break;
            case 'd':
                std::cout << "Descomprimindo..." << std::endl;
                break;
            case 's':
                std::cout << "Estatísticas..." << std::endl;
                break;
            case 'o':
                std::cout << "Redirecionando saída para arquivo " << optarg << std::endl;
                break;
            default:
                std::cout << "Uso: ./huff [MODO] <ARQUIVO> [OPÇÃO] ..." << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}