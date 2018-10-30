#include <iostream>
#include <map>
#include "huffTree.hpp"

Node::Node(char character, int frequency){
    // Define os atributos do nó criado
    this->character = character;
    this->frequency = frequency;
    this->left   = NULL;
    this->right  = NULL;
}

Node::Node(Node *leftNode, Node *rightNode){
    // Define os atributos do nó de soma criado
    this->character = '\0';
    this->code = "";
    this->frequency = leftNode->frequency + rightNode->frequency;
    this->left   = leftNode;
    this->right  = rightNode;
}

char Node::getCharacter(){
    // Retorna o caractere do nó
    return this->character;
}

int Node::getFrequency(){
    // Retorna a frequência do nó
    return this->frequency;
}

//Debug only
void Node::print(){

    if(!this->left && !this->right)
        std::cout << this->character << " - " << this->code << std::endl;  

    if(this->left != NULL)
        this->left->print();
    
    if(this->right != NULL)
        this->right->print();
}

void Node::fillCode(std::string code){

    // Verifica se um nó folha foi atingindo e seta o seu código gerado
    if(!this->left && !this->right)
        this->code = code;

    // Verifica se existe algum nó a esquerda, concatena o bit '0' ao código 
    // e ao retornar da recursão apaga o ultimo bit escrito
    if(this->left){
        code += '0';
        this->left->fillCode(code);
        code.erase(code.end()-1);
    }

    // Verifica se existe algum nó a direita, concatena o bit '1' ao código 
    // e ao retornar da recursão apaga o ultimo bit escrito
    if(this->right){
        code += '1';
        this->right->fillCode(code);
        code.erase(code.end()-1);
    }
}

void Node::fillCode(std::map<char,std::string>* codeMap){

    // Verifica se um nó folha foi atingido e acrescenta o seu código ao mapa de códigos
    if(!this->left && !this->right)  
        codeMap->insert(std::pair<char,std::string>(this->character,this->code));

    // Verifica se existe algum nó a esquerda e chama a recursão à esquerda
    if(this->left != NULL)
        this->left->fillCode(codeMap);

    // Verifica se existe algum nó a direita e chama a recursão à direita
    if(this->right != NULL)
        this->right->fillCode(codeMap);
}
