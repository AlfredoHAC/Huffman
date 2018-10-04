#include "huffman.hpp"

bool Comparable::operator()(Node *Node1, Node *Node2){
    return Node1->getFrequency() > Node2->getFrequency();
}

void Huffman::fillFrequencies(std::ifstream *file){
    char ch;

    *file >> std::noskipws;
    while(*file >> ch){
        this->mapIterator = this->frequencies.find(ch);

        if(this->mapIterator == this->frequencies.end()){
            this->frequencies.insert(std::pair<char,int>(ch,1));
        }else{
            this->mapIterator->second++;
        }
    }
    file->close();
    
    //debug
    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++)
        std::cout << this->mapIterator->first << " - " << this->mapIterator->second << std::endl;
}

void Huffman::fillQueue(){
    for(this->mapIterator = this->frequencies.begin(); this->mapIterator != this->frequencies.end(); this->mapIterator++){
        this->ordFrequencies.push(new Node(this->mapIterator->first, this->mapIterator->second));
    }

    //debug
    // std::cout << this->ordFrequencies.size() << std::endl;
    // int size = this->ordFrequencies.size();
    // for(int i = 0; i < size; i++){
    //     std::cout << this->ordFrequencies.top()->getCharacter() << " - " << this->ordFrequencies.top()->getFrequency() << std::endl;
    //     this->ordFrequencies.pop();
    // }
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
    this->huffTree->Print();
}

void Huffman::codify(){
    std::string code;
    this->huffTree->fillCode(code);
}