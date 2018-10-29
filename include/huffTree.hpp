#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

class Node{
    private:
        char character;
        int frequency;
        std::string code;
        
    public:
        Node *left;
        Node *right;
        Node(char, int);
        Node(Node *, Node *);
        char getCharacter();
        int getFrequency();
        void print(); //Debug only
        void fillCode(std::string);
        void fillCode(std::map<char,std::string>*);
};

#endif