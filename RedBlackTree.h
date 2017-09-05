#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED

#include<cstdlib>
#include<ctime>
#include<iostream>
#include"Node.h"

class RedBlackTree
{
    private:
        int blackHeight;//This is to keep track of the current black height of the Red-Black Tree. A random path will be followed down the tree to make sure that the Red-Black Tree remains valid for debugging purposes.
        int numberOfNodes;//This is to keep track of the total number of nodes in the Red-Black Tree.
        Node* root;//This is a pointer to the root node of the Red-Black Tree.

    public:
        RedBlackTree();
        ~RedBlackTree();
        void setBlackHeight(int);
        int getBlackHeight();
        void setNumberOfNodes(int);
        int getNumberOfNodes();
        void setRoot(Node*);
        Node* getRoot();
        void insertKey(int, Node*);
        void insertFixUp(Node*);
        void leftLeftRotate(Node*);//This is the rotation for the case, given a violated node n, where you have the combination of n, n->leftChild, n->leftChild->leftChild.
        void leftRightRotate(Node*);//This is the rotation for the case, given a violated node n, where you have the combination of n, n->leftChild, n->leftChild->rightChild.
        void rightLeftRotate(Node*);//This is the rotation for the case, given a violated node n, where you have the combination of n, n->rightChild, n->rightChild->leftChild.
        void rightRightRotate(Node*);//This is the rotation for the case, given a violated node n, where you have the combination of n, n->rightChild, n->rightChild->rightChild.
        void printInOrder(Node*);//This performs an in-order traversal of the Red-Black Tree, printing out the keys along with their respective colors in non-decreasing order.
        void searchKey(int, Node*);
        void removeKey(int, Node*);
        void removeFixUp(Node*);
        void clear(Node*);
        void calculateBlackHeight(Node*);//This calculates the black height of the Red-Black Tree by taking a random path from the root or the node argument. This will make sure that the Red-Black Tree will remain valid for debugging purposes.
        void longestPath(Node*);//This calculates the longest path from the node argument. If the node argument is the root of the Red-Black Tree this function will calculate the longest path of the Red-Black Tree. Theoretically, the longest path will have alternate red and black nodes usually. Also the longest path will have <= 2x the number of nodes of the shortest path on average.
        int height(Node*);//This calculates the height-level of the node argument in the Red-Black Tree that is passed to this function.
        void shortestPath(Node*);//This calculates the shortest path from the node argument. If the node argument is the root of the Red-Black Tree, this will calculate the shortest path of the Red-Black Tree. Theoretically, the shortest path will have only black nodes. Also, the shortest path will have <= 1/2 the number of nodes of the longest path on average.
        int diameter(Node*, int&);//This calculates the number of nodes from the deepest leaf on the left side of the Red-Black Tree to the deepest leaf on the right side of the Red-Black Tree from the node argument.
        int getLeafCount(Node*);//This counts how many leaf nodes are in the Red-Black Tree from the node argument. If the node argument is the root, this will calculate how many leaf nodes are in the Red-Black Tree.
        int width(Node*, int);//This gives the amount of nodes in a certain level in the Red-Black Tree from the node argument.
        void printByLevel();//This prints the Red-Black Tree in level order, using breadth first search.
        void printLevelOrder(int, Node*);//This prints the Node of the Red-Black Tree in the level provided by the int argument, provided that it is >=0. It is used in conjunction with the printByLevel() function.
};

#endif//REDBLACKTREE_H_INCLUDED
