

#include <iostream>
#include <fstream>
#include <clocale>
#include <unistd.h>
#include "huffman.hpp"
#include "huffTree.hpp"

int main(int argc, char *argv[]){

    // Permite o uso de acentos gráficos
    setlocale(LC_ALL, "");

    // Verifica se a quantidade de argumentos informados na execução está correta
    if(argc < 2){
        std::cerr << "Uso: huff [MODO] [OPÇÃO] ..." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Objeto Huffman responsável pelas funções do algoritmo
    Huffman *huff = new Huffman();

    // Variável auxiliar
    char ch;

    // Verifica nos argumentos a presença das opções
    while((ch = getopt(argc, argv, "ho:c:d:s:")) != EOF){

        // Verifica se a primeira opção é de redirecionamento da saída
        if((argv[1][1] == 'o')){
            std::cerr << "Huff: Falta Arquivo de Entrada" << std::endl;
            exit(EXIT_FAILURE);
        }

        switch(ch){
            // Opção 'Help'
            case 'h':
                std::cout << "Implementação do algoritmo de Huffman" << std::endl;
                std::cout << "Uso: huff [MODO] <ARQUIVO> [OPÇÃO] ..." << std::endl;
                std::cout << "MODO:" << std::endl;
                std::cout << "  -c <arquivo de entrada> \tComprime o arquivo especificado" << std::endl;
                std::cout << "  -d <arquivo comprimido> \tDescomprime um arquivo já comprimido" << std::endl;
                std::cout << "  -s <arquivo comprimido> \tMostra estatísticas sobre o arquivo comprimido" << std::endl;
                std::cout << std::endl << "OPÇÕES:" << std::endl;
                std::cout << "  -h \t\t\t\tMostra esse texto de ajuda" << std::endl;
                std::cout << "  -o <arquivo de saída> \tRedireciona a saída para o arquivo informado" << std::endl;
                std::cout << std::endl;
                break;
            // Opção 'Comprimir'
            case 'c':
                std::cout << "Comprimindo..." << optarg << std::endl << std::endl;
                huff->setInFile(optarg);

                huff->compress();
                
                break;
            // Opção 'Descomprimir'
            case 'd':
                std::cout << "Descomprimindo..." << optarg << std::endl << std::endl;
                huff->setInFile(optarg);
                huff->setOutFile("out.txt");
                
                huff->decompress();

                break;
            
            /* TODO */
            // Opção 'Estatisticas'
            case 's':
                std::cout << "Estatísticas..." << std::endl;

                break;

            /* TODO */
            // Opção 'Redirecionamento do arquivo de saída'
            case 'o':
                std::cout << "Redirecionando saída para arquivo " << optarg << std::endl;
                huff->setOutFile(optarg);
                
                break;
        
            default:
                std::cout << "Uso: ./huff [MODO] <ARQUIVO> [OPÇÃO] ..." << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    //Libera a memória do objeto da classe Huffman
    delete huff;

    return 0;
}