#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include<cstddef>

enum Color
{
    Black,
    Red
};

class Node
{
    private:
        int key;
        Color color;
        Node* leftChild;
        Node* rightChild;
        Node* parent;

    public:
        Node(int, Color, Node*, Node*, Node*);
        ~Node();
        void setKey(int);
        int getKey();
        void setColor(Color);
        Color getColor();
        void setLeftChild(Node*);
        Node* getLeftChild();
        void setRightChild(Node*);
        Node* getRightChild();
        void setParent(Node*);
        Node* getParent();
};

#endif//NODE_H_INCLUDED
