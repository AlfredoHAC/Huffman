#include "huffman.hpp"

Huffman::Huffman(){
    this->inFileName = "";
    this->outFileName = "out.huff";
}

Huffman::~Huffman(){

}

bool Huffman::Comparable::operator()(Node *Node1, Node *Node2){
    return Node1->getFrequency() > Node2->getFrequency();
}

void Huffman::setInFile(std::string inFileName){
    this->inFileName = inFileName;
}

void Huffman::setOutFile(std::string outFileName){
    this->outFileName = outFileName;
}

void Huffman::print(){
    std::cout << this->inFileName << std::endl;
    std::cout << this->outFileName << std::endl;
}

std::string Huffman::dec2bin(int decimal){
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

unsigned int Huffman::bin2dec(std::string binary){

    int resultado = 0;
    for(unsigned int i = 0; i < binary.size(); i++){
        resultado += (binary[i] - '0')*pow(2, binary.size() - i - 1);
    }
    return resultado;
}

void Huffman::fillFrequencies(){
    unsigned char ch;

    this->inFile >> std::noskipws;
    while(this->inFile.read((char *)&ch, 1)){
        this->frequencies[ch]++;
    }
}

void Huffman::fillQueue(){
    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++){
        this->ordFrequencies.push(new Node(this->mapIterator->first, this->mapIterator->second));
    }
}

void Huffman::buildTree(){
    Node *node1;
    Node *node2;
    Node *merged;

    while(this->ordFrequencies.size() > 1){
        node1 = this->ordFrequencies.top();
        this->ordFrequencies.pop();

        node2 = this->ordFrequencies.top();
        this->ordFrequencies.pop();

        merged = new Node(node1, node2);

        this->ordFrequencies.push(merged);    
    }

    this->huffTree = this->ordFrequencies.top();
}

//Debug only
void Huffman::printTree(){
    this->huffTree->print();
}

void Huffman::codify(){
    std::string code;
    this->huffTree->fillCode(code);
    this->huffTree->fillCode(&this->codes);
}

int Huffman::readHeader(){

    char filetype[5];

    this->inFile.read(filetype, 5);

    if(strcmp(filetype, "HUFF")){
        std::cerr << "Erro: Arquivo inválido" << std::endl;
        exit(EXIT_FAILURE);
    }

    int N = 0;
    this->inFile.read((char *)&N, 1);

    char character;
    int frequency;
    for(int i = 0; i < N; i++){
        this->inFile.read((char *)&character, 1);
        this->inFile.read((char *)&frequency, 4);

        this->frequencies[character] = frequency;
    }

    int padding = 0;
    this->inFile.read((char *)&padding, 1);

    return padding;
}

void Huffman::compress(){

    this->inFile.open(this->inFileName, std::ios::binary | std::ios::in);

    if(!this->inFile.is_open()){
        std::cerr << "Erro: Arquivo de entrada não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "[+] Calculando frequencias..." << std::endl;
    this->fillFrequencies();

    std::cout << "[+] Criando árvore de Huffman..." << std::endl;
    this->fillQueue();
    this->buildTree();

    std::cout << "[+] Calculando novos códigos..." << std::endl;
    this->codify();
    
    // for(int i = 0; i < 127; i++){
    //     if(this->codes[i] != "")
    //         std::cout << (char) i << " - " <<this->codes[i] << std::endl;
    // }
    
    this->inFile.clear();
    this->inFile.seekg(std::ios::beg);

    this->outFile.open(this->outFileName, std::ios::binary | std::ios::out);

    this->outFile << "HUFF" << '\0';
    this->outFile << (unsigned char) this->frequencies.size();

    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++){
        this->outFile << (unsigned char) this->mapIterator->first;

        this->outFile << (unsigned char)((this->mapIterator->second >> 0) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 8) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 16) & 0xff);
        this->outFile << (unsigned char)((this->mapIterator->second >> 24) & 0xff);
    }

    std::string temp = "";
    std::string newCode = "";
    unsigned char ch;
    int padding = 0;

    while(this->inFile >> ch){
        temp += this->codes[ch];
    
        if(temp.size() > 8){
            newCode += (unsigned char)this->bin2dec(temp.substr(0,8));
            temp = temp.substr(8);
        }
    }


    if(temp.size() < 8){
        padding = 8 - temp.size();
        temp.append(padding, '0');
    }

    newCode += (unsigned char)bin2dec(temp); 
    this->outFile << (unsigned char) padding;

    this->outFile.write(newCode.c_str(), newCode.size());

    this->inFile.close();
    this->outFile.close();

}

void Huffman::decompress(){

    this->inFile.open(this->inFileName, std::ios::binary | std::ios::in);

    if(!this->inFile.is_open()){
        std::cerr << "Erro: Arquivo não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "[+] Lendo cabeçalho do arquivo" << std::endl;
    int padding = this->readHeader();

    std::cout << "[+] Construíndo árvore de Huffman" << std::endl;
    this->fillQueue();
    this->buildTree();

    std::cout << "[+] Calculando novos códigos" << std::endl;
    this->codify();

    // this->huffTree->print();

    // this->inFile.read((char *)&padding, 1);

    int decimalCode = 0;
    std::string binaryCode;
    while(this->inFile.read((char *)&decimalCode, 1)){
        binaryCode += this->dec2bin(decimalCode);
    }

    binaryCode.erase(binaryCode.size() - padding);

    this->outFile.open(this->outFileName, std::ios::binary | std::ios::out);
    
    Node *cursor = this->huffTree;
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


    this->inFile.close();
    this->outFile.close();
}
