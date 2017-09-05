#include"Node.h"

Node::Node(int key, Color color, Node* leftChild, Node* rightChild, Node* parent)
{
    this->setKey(key);
    this->setColor(color);
    this->setLeftChild(leftChild);
    this->setRightChild(rightChild);
    this->setParent(parent);
}

Node::~Node()
{
    this->setKey(0);
    this->setColor(Black);
    this->setLeftChild(NULL);
    this->setRightChild(NULL);
    this->setParent(NULL);
}

void Node::setKey(int key)
{
    this->key=key;
}

int Node::getKey()
{
    return this->key;
}

void Node::setColor(Color color)
{
    this->color=color;
}

Color Node::getColor()
{
    return this->color;
}

void Node::setLeftChild(Node* leftChild)
{
    this->leftChild=leftChild;
}

Node* Node::getLeftChild()
{
    return this->leftChild;
}

void Node::setRightChild(Node* rightChild)
{
    this->rightChild=rightChild;
}

Node* Node::getRightChild()
{
    return this->rightChild;
}

void Node::setParent(Node* parent)
{
    this->parent=parent;
}

Node* Node::getParent()
{
    return this->parent;
}
