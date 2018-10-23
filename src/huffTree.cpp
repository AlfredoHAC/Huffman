#include <iostream>
<<<<<<< HEAD
=======
#include <map>
>>>>>>> Compressão/Descompressão Implementada
#include "huffTree.hpp"

Node::Node(char character, int frequency){
    this->character = character;
    this->frequency = frequency;
    this->left   = NULL;
    this->right  = NULL;
}

Node::Node(Node *LeftNode, Node *RightNode){
<<<<<<< HEAD
=======
    this->character = '\0';
    this->code = "";
>>>>>>> Compressão/Descompressão Implementada
    this->frequency = LeftNode->frequency + RightNode->frequency;
    this->left   = LeftNode;
    this->right  = RightNode;
}

char Node::getCharacter(){
    return this->character;
}

int Node::getFrequency(){
    return this->frequency;
}

//Debug only
<<<<<<< HEAD
void Node::Print(){

    if(!this->left && !this->right)
        std::cout << this->character << " - " << this->code << std::endl;  
    
    if(this->left != NULL)
        this->left->Print();
    
    if(this->right != NULL)
        this->right->Print();
=======
void Node::print(){

    if(!this->left && !this->right)
        std::cout << this->character << " - " << this->code << std::endl;  

    if(this->left != NULL)
        this->left->print();
    
    if(this->right != NULL)
        this->right->print();
>>>>>>> Compressão/Descompressão Implementada
}

void Node::fillCode(std::string code){
    if(!this->left && !this->right){
        this->code = code;
    }
    if(this->left){
        code += '0';
        this->left->fillCode(code);
        code.erase(code.end()-1);
    }
    if(this->right){
        code += '1';
        this->right->fillCode(code);
        code.erase(code.end()-1);
    }
}

<<<<<<< HEAD
=======
void Node::fillCode(std::map<char,std::string>* CodeMap){
    if(!this->left && !this->right)  
        CodeMap->insert(std::pair<char,std::string>(this->character,this->code));

    if(this->left != NULL)
        this->left->fillCode(CodeMap);
    
    if(this->right != NULL)
        this->right->fillCode(CodeMap);
}
>>>>>>> Compressão/Descompressão Implementada
