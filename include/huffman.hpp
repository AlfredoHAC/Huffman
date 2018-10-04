#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include "huffTree.hpp"

class Comparable{
    public:
        bool operator()(Node *, Node *);
};

class Huffman{
    private:
        Node *huffTree;
        std::map<char,int> frequencies;
        std::map<char,int>::iterator mapIterator;
        std::priority_queue<Node *, std::vector<Node *>, Comparable> ordFrequencies;
    public:
        void fillFrequencies(std::ifstream *);
        void fillQueue();
        void buildTree();
        void printTree(); //Debug only
        void codify();
        void compress();
        void decompress();
};

#endif