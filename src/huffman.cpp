#include "huffman.hpp"

Huffman::Huffman(){
    // Seta vazio o nome do arquivo de entrada
    this->inFileName = "";

    // Seta o nome padrão dos arquivos de saída
    this->outFileName = "out.huff";

    // Cria o objeto de conversão binário <--> decimal
    this->converter = new BinDecConverter();
}

Huffman::~Huffman(){

}

bool Huffman::Comparable::operator()(Node *Node1, Node *Node2){
    // Verifica se o primeiro nó tem frequência maior que o segundo
    return Node1->getFrequency() > Node2->getFrequency();
}

void Huffman::setInFile(std::string inFileName){
    // Seta o nome do arquivo de entrada para o nome informado no parâmetro
    this->inFileName = inFileName;
}

void Huffman::setOutFile(std::string outFileName){
    // Seta o nome do arquivo de saída para o nome informado no parâmetro
    this->outFileName = outFileName;
}

//Debug Only
void Huffman::print(){
    std::cout << this->inFileName << std::endl;
    std::cout << this->outFileName << std::endl;
}


void Huffman::fillFrequencies(){
    // Variável auxiliar para leitura dos caracteres do arquivo
    unsigned char ch;

    // Força a leitura de espaços e quebras de linha no arquivo
    this->inFile >> std::noskipws;
    
    // Lê cada byte do arquivo e preenche o mapa de frequencias
    while(this->inFile.read((char *)&ch, 1)){
        this->frequencies[ch]++;
    }
}

void Huffman::fillQueue(){
    // Lê cada caractere e sua frequencia e cria um nó para posterior construção da árvore de Huffman
    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++){
        this->ordFrequencies.push(new Node(this->mapIterator->first, this->mapIterator->second));
    }
}

void Huffman::buildTree(){

    // Variaveis auxiliares 
    Node *node1;
    Node *node2;
    Node *merged;

    // Soma a frequência dos nós de menor frequência e torna este como nó raiz dos nós somados
    while(this->ordFrequencies.size() > 1){
        node1 = this->ordFrequencies.top();
        this->ordFrequencies.pop();

        node2 = this->ordFrequencies.top();
        this->ordFrequencies.pop();

        merged = new Node(node1, node2);

        this->ordFrequencies.push(merged);    
    }

    // Define a raiz da árvore de Huffman como o último elemento da fila
    this->huffTree = this->ordFrequencies.top();
}

//Debug only
void Huffman::printTree(){
    this->huffTree->print();
}

void Huffman::codify(){
    // Variável contendo o código temporário de cada caractere
    std::string code;
    
    // Preenche o código de cada nó folha da árvore de Huffman
    this->huffTree->fillCode(code);
    
    // Preenche o mapa de códigos dos caracteres
    this->huffTree->fillCode(&this->codes);
}

int Huffman::readHeader(){

    // Variável auxiliar
    char filetype[5];

    // Lê os 5 primeiros bytes e verifica se o arquivo é válido para descompressão
    this->inFile.read(filetype, 5);

    if(strcmp(filetype, "HUFF")){
        std::cerr << "Erro: Arquivo inválido" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Lê no cabeçalho a quantidade de caracteres distintos presentes no arquivo comprimido
    int N = 0;
    this->inFile.read((char *)&N, 1);

    // Preenche o mapa de frequências de acordo com o cabeçalho do arquivo comprimido
    char character;
    int frequency;
    for(int i = 0; i < N; i++){
        this->inFile.read((char *)&character, 1);
        this->inFile.read((char *)&frequency, 4);

        this->frequencies[character] = frequency;
    }

    // Lê o padding do arquivo comprimido
    int padding = 0;
    this->inFile.read((char *)&padding, 1);

    // Retorna o padding
    return padding;
}

void Huffman::compress(){

    // Faz a abertura do arquivo de entrada para compressão
    this->inFile.open(this->inFileName, std::ios::binary | std::ios::in);

    // Verifica se o arquivo abriu com sucesso
    if(!this->inFile.is_open()){
        std::cerr << "Erro: Arquivo de entrada não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Preenche o mapa de frequências
    std::cout << "[+] Calculando frequencias...";
    this->fillFrequencies();
    std::cout << "OK" << std::endl;

    // Preenche a priority queue e cria a árvore de Huffman
    std::cout << "[+] Criando árvore de Huffman...";
    this->fillQueue();
    this->buildTree();
    std::cout << "OK" << std::endl;

    // Gera os novos códigos para cada caractere
    std::cout << "[+] Calculando novos códigos...";
    this->codify();
    std::cout << "OK" << std::endl;
    
    // Reposiciona o ponteiro do arquivo para o começo dele, para que seja feito a compressão
    this->inFile.clear();
    this->inFile.seekg(std::ios::beg);

    // Abre o arquivo de saída
    this->outFile.open(this->outFileName, std::ios::binary | std::ios::out);

    /*
     * Escrita do cabeçalho no arquivo
     */

    // Escreve o tipo do arquivo para reconhecimento da validade do arquivo comprimido
    this->outFile << "HUFF" << '\0';

    // Escreve a quantidade de caracteres distintos do arquivo de entrada
    this->outFile << (unsigned char) this->frequencies.size();

    // Escreve o caractere e sua frequência em formato Little Endian
    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++){
        this->outFile << (unsigned char) this->mapIterator->first;

        this->outFile << (unsigned char)((this->mapIterator->second >> 0) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 8) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 16) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 24) & 0xff);
    }

    // Variaveis auxiliares para a preparação dos blocos de 8 bytes
    std::string temp = "";
    std::string newCode = "";
    unsigned char ch;
    int padding = 0;


    // Prepara blocos de 8 bytes contendo os códigos gerados dos caracteres
    while(this->inFile >> ch){
        temp += this->codes[ch];
    
        
        if(temp.size() > 8){
            // Transforma o bloco de 8 bytes em inteiro para a escrita no arquivo
            newCode += (unsigned char)this->converter->bin2dec(temp.substr(0,8));
            
            temp = temp.substr(8);
        }
    }

    // Calcula o padding
    if(temp.size() < 8){
        padding = 8 - temp.size();
        temp.append(padding, '0');
    }

    // Gera o último código somado ao padding
    newCode += (unsigned char)this->converter->bin2dec(temp);

    // Esceve no cabeçalho o padding do arquivo comprimido 
    this->outFile << (unsigned char) padding;

    // Escreve o novo código gerado do texto de entrada
    this->outFile.write(newCode.c_str(), newCode.size());

    // Fecha os arquivos de entrada e de saída
    this->inFile.close();
    this->outFile.close();

    std::cout << std::endl << "[=] Arquivo Comprimido com Sucesso!" << std::endl;
}

void Huffman::decompress(){

    // Abre o arquivo de entrada
    this->inFile.open(this->inFileName, std::ios::binary | std::ios::in);

    // Verifica se o arquivo de entrada foi aberto com sucesso
    if(!this->inFile.is_open()){
        std::cerr << "Erro: Arquivo não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Lê o cabeçalho do arquivo comprimido
    std::cout << "[+] Lendo cabeçalho do arquivo...";
    int padding = this->readHeader();
    std::cout << "OK" << std::endl;
    // Constrói a árvore de Huffman baseado nas frequências presentes no cabeçalho
    std::cout << "[+] Construíndo árvore de Huffman...";
    this->fillQueue();
    this->buildTree();
    std::cout << "OK" << std::endl;

    // Gera os códigos de cada caractere 
    std::cout << "[+] Calculando códigos dos caracteres...";
    this->codify();
    std::cout << "OK" << std::endl;

    // Variáveis de auxilio para a leitura do código comprimido
    int decimalCode = 0;
    std::string binaryCode;
    
    // Lê cada byte como um inteiro e o converte para uma cadeia binária
    while(this->inFile.read((char *)&decimalCode, 1)){
        binaryCode += this->converter->dec2bin(decimalCode);
    }

    // Faz a remoção do padding do arquivo comprimido
    binaryCode.erase(binaryCode.size() - padding);

    // Abre o arquivo de saída
    this->outFile.open(this->outFileName, std::ios::binary | std::ios::out);

    // Variável auxiliar para percorrer a árvore de Huffman
    Node *cursor = this->huffTree;

    // Percorre a árvore para encontrar o caractere correspondente ao código lido
    for(unsigned int i = 0; i < binaryCode.size(); i++){
        if((cursor->left) && (binaryCode[i] == '0'))
            cursor = cursor->left;
        if((cursor->right) && (binaryCode[i] == '1'))
            cursor = cursor->right;
        if(!cursor->left && !cursor->right){
            this->outFile << cursor->getCharacter();
            cursor = this->huffTree;
        }
    }

    // Fecha os arquivos de entrada e saída
    this->inFile.close();
    this->outFile.close();

    std::cout << std::endl << "[=] Arquivo Descomprimido com Sucesso!" << std::endl;
}
