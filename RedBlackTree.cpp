#include"RedBlackTree.h"

RedBlackTree::RedBlackTree()
{
    this->setBlackHeight(0);
    this->setNumberOfNodes(0);
    this->setRoot(NULL);
}

RedBlackTree::~RedBlackTree()
{
    this->setBlackHeight(0);
    this->setNumberOfNodes(0);
    this->clear(this->getRoot());
    this->setRoot(NULL);
}

void RedBlackTree::setBlackHeight(int blackHeight)
{
    this->blackHeight=blackHeight;
}

int RedBlackTree::getBlackHeight()
{
    return this->blackHeight;
}

void RedBlackTree::setNumberOfNodes(int numberOfNodes)
{
    this->numberOfNodes=numberOfNodes;
}

int RedBlackTree::getNumberOfNodes()
{
    return this->numberOfNodes;
}

void RedBlackTree::setRoot(Node* root)
{
    this->root=root;
}

Node* RedBlackTree::getRoot()
{
    return this->root;
}

void RedBlackTree::insertKey(int key, Node* insertNode)
{
    if(this->getRoot()==NULL)
    {
        this->setRoot(new Node(key, Red, NULL, NULL, NULL));
        this->insertFixUp(this->getRoot());
        this->setNumberOfNodes(this->getNumberOfNodes()+1);
    }

    else
    {
        if(key<insertNode->getKey())
        {
            if(insertNode->getLeftChild()==NULL)
            {
                insertNode->setLeftChild(new Node(key, Red, NULL, NULL, insertNode));
                this->insertFixUp(insertNode->getLeftChild());
                this->setNumberOfNodes(this->getNumberOfNodes()+1);
            }

            else
            {
                this->insertKey(key, insertNode->getLeftChild());
            }
        }

        else
        {
            if(insertNode->getRightChild()==NULL)
            {
                insertNode->setRightChild(new Node(key, Red, NULL, NULL, insertNode));
                this->insertFixUp(insertNode->getRightChild());
                this->setNumberOfNodes(this->getNumberOfNodes()+1);
            }

            else
            {
                this->insertKey(key, insertNode->getRightChild());
            }
        }
    }
}

void RedBlackTree::insertFixUp(Node* fixNode)
{
    if(fixNode->getColor()==Red)
    {
        if(fixNode==this->getRoot())
        {
            fixNode->setColor(Black);
        }

        else
        {
            if(fixNode->getParent()!=NULL&&fixNode->getParent()->getColor()==Red)//Here we check if we have two adjacent red nodes.
            {
                if(fixNode->getParent()->getParent()!=NULL)//Here we check if the node has a grandparent because if doesn't have a grandparent, it cannot have an uncle.
                {
                    Node* uncle=NULL;
                    if(fixNode->getParent()->getParent()->getLeftChild()==fixNode->getParent())
                    {
                        uncle=fixNode->getParent()->getParent()->getRightChild();
                    }

                    else
                    {
                        uncle=fixNode->getParent()->getParent()->getLeftChild();
                    }

                    if(uncle==NULL||uncle->getColor()==Black)//Since uncle is black we will have to perform rotations and recoloring to restore Red-Black Tree properties.
                    {
                        if(fixNode->getParent()->getParent()->getLeftChild()==fixNode->getParent())
                        {
                            if(fixNode->getParent()->getLeftChild()==fixNode)//Left-Left Rotation is needed.
                            {
                                this->leftLeftRotate(fixNode->getParent()->getParent());
                                fixNode->getParent()->getRightChild()->setColor(Red);
                                fixNode->getParent()->setColor(Black);
                            }

                            else//Left-Right Rotation is needed.
                            {
                                this->leftRightRotate(fixNode->getParent()->getParent());
                                fixNode->getLeftChild()->setColor(Red);
                                fixNode->getRightChild()->setColor(Red);
                                fixNode->setColor(Black);
                            }
                        }

                        else//We have a Right-Right violation, mirror of first case.
                        {
                            if(fixNode->getParent()->getLeftChild()==fixNode)//Right-Left Rotation is needed.
                            {
                                this->rightLeftRotate(fixNode->getParent()->getParent());
                                fixNode->getLeftChild()->setColor(Red);
                                fixNode->getRightChild()->setColor(Red);
                                fixNode->setColor(Black);
                            }

                            else//Right-Right Rotation is needed.
                            {
                                this->rightRightRotate(fixNode->getParent()->getParent());
                                fixNode->getParent()->getLeftChild()->setColor(Red);
                                fixNode->getParent()->setColor(Black);
                            }
                        }

                        if(uncle!=NULL)
                        {
                            uncle=NULL;
                        }
                    }

                    else//Uncle is Red so we will have to do re-colorings and move the violation up to the grandparent.
                    {
                        fixNode->getParent()->setColor(Black);
                        uncle->setColor(Black);
                        fixNode->getParent()->getParent()->setColor(Red);
                        uncle=NULL;
                        this->insertFixUp(fixNode->getParent()->getParent());
                    }
                }
            }
        }
    }
}

void RedBlackTree::leftLeftRotate(Node* AVLNode)
{
    if(AVLNode==this->getRoot())
    {
        Node* AVLNode2=AVLNode->getLeftChild();
        AVLNode->setLeftChild(AVLNode2->getRightChild());
        AVLNode2->setRightChild(AVLNode);
        AVLNode->setParent(AVLNode2);

        if(AVLNode->getLeftChild()!=NULL)
        {
            AVLNode->getLeftChild()->setParent(AVLNode);
        }

        AVLNode2->setParent(NULL);
        this->setRoot(AVLNode2);

        AVLNode2=NULL;
    }

    else
    {
        Node* AVLNode2=AVLNode->getParent();
        Node* AVLNode3=AVLNode->getLeftChild();
        AVLNode->setLeftChild(AVLNode3->getRightChild());
        AVLNode3->setRightChild(AVLNode);
        AVLNode->setParent(AVLNode3);

        if(AVLNode->getLeftChild()!=NULL)
        {
            AVLNode->getLeftChild()->setParent(AVLNode);
        }

        AVLNode3->setParent(AVLNode2);

        if(AVLNode2->getLeftChild()==AVLNode)
        {
            AVLNode2->setLeftChild(AVLNode3);
        }

        else
        {
            AVLNode2->setRightChild(AVLNode3);
        }

        AVLNode2=NULL;
        AVLNode3=NULL;
    }
}

void RedBlackTree::leftRightRotate(Node* AVLNode)
{
    if(AVLNode==this->getRoot())
    {
        Node* AVLNode2=AVLNode->getLeftChild();
        Node* AVLNode3=AVLNode2->getRightChild();
        AVLNode->setLeftChild(AVLNode3->getRightChild());
        AVLNode3->setRightChild(AVLNode);
        AVLNode2->setRightChild(AVLNode3->getLeftChild());
        AVLNode3->setLeftChild(AVLNode2);
        AVLNode->setParent(AVLNode3);
        AVLNode2->setParent(AVLNode3);

        if(AVLNode->getLeftChild()!=NULL)
        {
            AVLNode->getLeftChild()->setParent(AVLNode);
        }

        if(AVLNode2->getRightChild()!=NULL)
        {
            AVLNode2->getRightChild()->setParent(AVLNode2);
        }

        AVLNode3->setParent(NULL);
        this->setRoot(AVLNode3);

        AVLNode2=NULL;
        AVLNode3=NULL;
    }

    else
    {
        Node* AVLNode2=AVLNode->getParent();
        Node* AVLNode3=AVLNode->getLeftChild();
        Node* AVLNode4=AVLNode3->getRightChild();
        AVLNode->setLeftChild(AVLNode4->getRightChild());
        AVLNode4->setRightChild(AVLNode);
        AVLNode3->setRightChild(AVLNode4->getLeftChild());
        AVLNode4->setLeftChild(AVLNode3);
        AVLNode->setParent(AVLNode4);
        AVLNode3->setParent(AVLNode4);

        if(AVLNode->getLeftChild()!=NULL)
        {
            AVLNode->getLeftChild()->setParent(AVLNode);
        }

        if(AVLNode3->getRightChild()!=NULL)
        {
            AVLNode3->getRightChild()->setParent(AVLNode3);
        }

        AVLNode4->setParent(AVLNode2);

        if(AVLNode2->getLeftChild()==AVLNode)
        {
            AVLNode2->setLeftChild(AVLNode4);
        }

        else
        {
            AVLNode2->setRightChild(AVLNode4);
        }

        AVLNode2=NULL;
        AVLNode3=NULL;
        AVLNode4=NULL;
    }
}

void RedBlackTree::rightLeftRotate(Node* AVLNode)
{
    if(AVLNode==this->getRoot())
    {
        Node* AVLNode2=AVLNode->getRightChild();
        Node* AVLNode3=AVLNode2->getLeftChild();
        AVLNode->setRightChild(AVLNode3->getLeftChild());
        AVLNode3->setLeftChild(AVLNode);
        AVLNode2->setLeftChild(AVLNode3->getRightChild());
        AVLNode3->setRightChild(AVLNode2);
        AVLNode->setParent(AVLNode3);
        AVLNode2->setParent(AVLNode3);

        if(AVLNode->getRightChild()!=NULL)
        {
            AVLNode->getRightChild()->setParent(AVLNode);
        }

        if(AVLNode2->getLeftChild()!=NULL)
        {
            AVLNode2->getLeftChild()->setParent(AVLNode2);
        }

        AVLNode3->setParent(NULL);
        this->setRoot(AVLNode3);

        AVLNode2=NULL;
        AVLNode3=NULL;
    }

    else
    {
        Node* AVLNode2=AVLNode->getParent();
        Node* AVLNode3=AVLNode->getRightChild();
        Node* AVLNode4=AVLNode3->getLeftChild();
        AVLNode->setRightChild(AVLNode4->getLeftChild());
        AVLNode4->setLeftChild(AVLNode);
        AVLNode3->setLeftChild(AVLNode4->getRightChild());
        AVLNode4->setRightChild(AVLNode3);
        AVLNode->setParent(AVLNode4);
        AVLNode3->setParent(AVLNode4);

        if(AVLNode->getRightChild()!=NULL)
        {
            AVLNode->getRightChild()->setParent(AVLNode);
        }

        if(AVLNode3->getLeftChild()!=NULL)
        {
            AVLNode3->getLeftChild()->setParent(AVLNode3);
        }

        AVLNode4->setParent(AVLNode2);

        if(AVLNode2->getLeftChild()==AVLNode)
        {
            AVLNode2->setLeftChild(AVLNode4);
        }

        else
        {
            AVLNode2->setRightChild(AVLNode4);
        }

        AVLNode2=NULL;
        AVLNode3=NULL;
        AVLNode4=NULL;
    }
}

void RedBlackTree::rightRightRotate(Node* AVLNode)
{
    if(AVLNode==this->getRoot())
    {
        Node* AVLNode2=AVLNode->getRightChild();
        AVLNode->setRightChild(AVLNode2->getLeftChild());
        AVLNode2->setLeftChild(AVLNode);
        AVLNode->setParent(AVLNode2);

        if(AVLNode->getRightChild()!=NULL)
        {
            AVLNode->getRightChild()->setParent(AVLNode);
        }

        AVLNode2->setParent(NULL);
        this->setRoot(AVLNode2);

        AVLNode2=NULL;
    }

    else
    {
        Node* AVLNode2=AVLNode->getParent();
        Node* AVLNode3=AVLNode->getRightChild();
        AVLNode->setRightChild(AVLNode3->getLeftChild());
        AVLNode3->setLeftChild(AVLNode);
        AVLNode->setParent(AVLNode3);

        if(AVLNode->getRightChild()!=NULL)
        {
            AVLNode->getRightChild()->setParent(AVLNode);
        }

        AVLNode3->setParent(AVLNode2);

        if(AVLNode2->getLeftChild()==AVLNode)
        {
            AVLNode2->setLeftChild(AVLNode3);
        }

        else
        {
            AVLNode2->setRightChild(AVLNode3);
        }

        AVLNode2=NULL;
        AVLNode3=NULL;
    }
}

void RedBlackTree::printInOrder(Node* printNode)
{
    if(this->getRoot()==NULL)
    {
        std::cout<<"There are currently no keys in the Red-Black Tree to print. Please insert some keys into the Red-Black Tree using the appropriate menu choice in order to print them later."<<std::endl;
    }

    else
    {
        if(printNode->getLeftChild()!=NULL)
        {
            this->printInOrder(printNode->getLeftChild());
        }

        std::cout<<"Key: "<<printNode->getKey()<<" ";

        if(printNode->getColor()==Black)
        {
            std::cout<<"Color: Black"<<std::endl;
        }

        else
        {
            std::cout<<"Color: Red"<<std::endl;
        }

        if(printNode->getRightChild()!=NULL)
        {
            this->printInOrder(printNode->getRightChild());
        }
    }
}

void RedBlackTree::searchKey(int key, Node* searchNode)
{
    if(this->getRoot()==NULL)
    {
        std::cout<<"The Red-Black Tree is currently empty. Please insert some keys into the Red-Black Tree using the appropriate menu choice to search for them later.\n"<<std::endl;
    }

    else
    {
        if(key==searchNode->getKey())
        {
            std::cout<<"The key "<<key<<" has been found in the Red-Black Tree. It is at Node "<<searchNode<<"\n"<<std::endl;
        }

        else if(key<searchNode->getKey())
        {
            if(searchNode->getLeftChild()==NULL)
            {
                std::cout<<"The key "<<key<<" could not be found in the Red-Black Tree.\n"<<std::endl;
            }

            else
            {
                this->searchKey(key, searchNode->getLeftChild());
            }
        }

        else
        {
            if(searchNode->getRightChild()==NULL)
            {
                std::cout<<"The key "<<key<<" could not be found in the Red-Black Tree.\n"<<std::endl;
            }

            else
            {
                this->searchKey(key, searchNode->getRightChild());
            }
        }
    }
}

void RedBlackTree::removeKey(int key, Node* removeNode)
{
    if(this->getRoot()==NULL)
    {
        std::cout<<"There are no keys to remove from the Red-Black Tree. Please insert some keys into the Red-Black Tree using the appropriate menu choice in order to remove them later.\n"<<std::endl;
    }

    else
    {
        if(key==removeNode->getKey())
        {
            if(removeNode->getLeftChild()==NULL&&removeNode->getRightChild()==NULL)
            {
                Color removedColor=removeNode->getColor();
                Node* fixNode=removeNode->getParent();
                bool isRoot=false;
                bool isLeftChild=false;

                if(removeNode==this->getRoot())
                {
                    delete removeNode;
                    removeNode=NULL;
                    this->setRoot(NULL);
                    isRoot=true;
                }

                else
                {
                    if(removeNode->getParent()->getLeftChild()==removeNode)
                    {
                        removeNode->getParent()->setLeftChild(NULL);
                        isLeftChild=true;
                    }

                    else
                    {
                        removeNode->getParent()->setRightChild(NULL);
                    }

                    delete removeNode;
                    removeNode=NULL;
                }

                if(removedColor==Black)
                {
                    if(isRoot==false)
                    {
                        Node* nullLeaf=new (&removeNode) Node(0, removedColor, NULL, NULL, fixNode);//This makes a new Node object at the address where the removed node was originally.

                        if(isLeftChild==true)
                        {
                            fixNode->setLeftChild(nullLeaf);
                            this->removeFixUp(nullLeaf);
                            fixNode->setLeftChild(NULL);
                        }

                        else
                        {
                            fixNode->setRightChild(nullLeaf);
                            this->removeFixUp(nullLeaf);
                            fixNode->setRightChild(NULL);
                        }

                        delete nullLeaf;
                        nullLeaf=NULL;
                    }
                }

                if(fixNode!=NULL)
                {
                    fixNode=NULL;
                }
            }

            else if(removeNode->getLeftChild()!=NULL&&removeNode->getRightChild()==NULL)
            {
                Color removedColor=removeNode->getColor();
                Node* fixNode=removeNode->getLeftChild();

                if(removeNode==this->getRoot())
                {
                    this->setRoot(this->getRoot()->getLeftChild());
                    delete removeNode;
                    removeNode=NULL;
                    this->getRoot()->setParent(NULL);
                }

                else
                {
                    removeNode->getLeftChild()->setParent(removeNode->getParent());

                    if(removeNode->getParent()->getLeftChild()==removeNode)
                    {
                        removeNode->getParent()->setLeftChild(removeNode->getLeftChild());
                    }

                    else
                    {
                        removeNode->getParent()->setRightChild(removeNode->getLeftChild());
                    }

                    delete removeNode;
                    removeNode=NULL;
                }

                if(removedColor==Black)
                {
                    this->removeFixUp(fixNode);
                }

                fixNode=NULL;
            }

            else if(removeNode->getLeftChild()==NULL&&removeNode->getRightChild()!=NULL)
            {
                Color removedColor=removeNode->getColor();
                Node* fixNode=removeNode->getRightChild();

                if(removeNode==this->getRoot())
                {
                    this->setRoot(this->getRoot()->getRightChild());
                    delete removeNode;
                    removeNode=NULL;
                    this->getRoot()->setParent(NULL);
                }

                else
                {
                    removeNode->getRightChild()->setParent(removeNode->getParent());

                    if(removeNode->getParent()->getLeftChild()==removeNode)
                    {
                        removeNode->getParent()->setLeftChild(removeNode->getRightChild());
                    }

                    else
                    {
                        removeNode->getParent()->setRightChild(removeNode->getRightChild());
                    }

                    delete removeNode;
                    removeNode=NULL;
                }

                if(removedColor==Black)
                {
                    this->removeFixUp(fixNode);
                }

                fixNode=NULL;
            }

            else
            {
                Color removedColor=Black;
                Node* fixNode=NULL;
                bool isRightChildAdded=false;

                Node* removeNode2=removeNode->getRightChild();

                if(removeNode2->getLeftChild()==NULL)
                {
                    removedColor=removeNode2->getColor();
                    fixNode=removeNode2->getRightChild();
                    if(fixNode==NULL&&removedColor==Black)
                    {
                        removeNode2->setRightChild(new Node(0, Black, NULL, NULL, removeNode2));
                        fixNode=removeNode2->getRightChild();
                        isRightChildAdded=true;
                    }

                    removeNode->getLeftChild()->setParent(removeNode2);
                    removeNode2->setLeftChild(removeNode->getLeftChild());

                    if(removeNode==this->getRoot())
                    {
                        this->setRoot(removeNode2);
                        this->getRoot()->setParent(NULL);
                    }

                    else
                    {
                        removeNode2->setParent(removeNode->getParent());

                        if(removeNode->getParent()->getLeftChild()==removeNode)
                        {
                            removeNode->getParent()->setLeftChild(removeNode2);
                        }

                        else
                        {
                             removeNode->getParent()->setRightChild(removeNode2);
                        }
                    }

                    removeNode2->setColor(removeNode->getColor());
                }

                else
                {
                    Node* removeNode3=removeNode2->getLeftChild();

                    while(removeNode3->getLeftChild()!=NULL)
                    {
                        removeNode3=removeNode3->getLeftChild();
                    }

                    removedColor=removeNode3->getColor();
                    fixNode=removeNode3->getRightChild();
                    if(fixNode==NULL&&removedColor==Black)
                    {
                        removeNode3->setRightChild(new Node(0, Black, NULL, NULL, removeNode3));
                        fixNode=removeNode3->getRightChild();
                        isRightChildAdded=true;
                    }

                    if(removeNode3->getRightChild()!=NULL)
                    {
                        removeNode3->getRightChild()->setParent(removeNode3->getParent());
                    }

                    removeNode3->getParent()->setLeftChild(removeNode3->getRightChild());
                    removeNode2->setParent(removeNode3);
                    removeNode3->setRightChild(removeNode2);
                    removeNode->getLeftChild()->setParent(removeNode3);
                    removeNode3->setLeftChild(removeNode->getLeftChild());

                    if(removeNode==this->getRoot())
                    {
                        this->setRoot(removeNode3);
                        this->getRoot()->setParent(NULL);
                    }

                    else
                    {
                        removeNode3->setParent(removeNode->getParent());

                        if(removeNode->getParent()->getLeftChild()==removeNode)
                        {
                            removeNode->getParent()->setLeftChild(removeNode3);
                        }

                        else
                        {
                             removeNode->getParent()->setRightChild(removeNode3);
                        }
                    }

                    removeNode3->setColor(removeNode->getColor());
                    removeNode3=NULL;
                }

                delete removeNode;
                removeNode=NULL;
                removeNode2=NULL;

                if(removedColor==Black)
                {
                    this->removeFixUp(fixNode);
                }

                if(fixNode!=NULL)
                {
                    if(isRightChildAdded==true)
                    {
                        if(fixNode->getParent()->getLeftChild()==fixNode)
                        {
                            fixNode->getParent()->setLeftChild(NULL);
                        }

                        else
                        {
                            fixNode->getParent()->setRightChild(NULL);
                        }

                        delete fixNode;
                    }

                    fixNode=NULL;
                }
            }

            std::cout<<"The key "<<key<<" has successfully been removed from the Red-Black Tree.\n"<<std::endl;
            this->setNumberOfNodes(this->getNumberOfNodes()-1);
        }

        else if(key<removeNode->getKey())
        {
            if(removeNode->getLeftChild()!=NULL)
            {
                this->removeKey(key, removeNode->getLeftChild());
            }

            else
            {
                std::cout<<"The key "<<key<<" could not be found in the Red-Black Tree for removal.\n"<<std::endl;
            }
        }

        else
        {
            if(removeNode->getRightChild()!=NULL)
            {
                this->removeKey(key, removeNode->getRightChild());
            }

            else
            {
                std::cout<<"The key "<<key<<" could not be found in the Red-Black Tree for removal.\n"<<std::endl;
            }
        }
    }
}

void RedBlackTree::removeFixUp(Node* fixNode)
{
    if(fixNode==this->getRoot())
    {
        fixNode->setColor(Black);
    }

    else
    {
        if(fixNode->getParent()->getLeftChild()==fixNode&&fixNode->getParent()->getRightChild()!=NULL)//Sibling is parent's right child.
        {
            if(fixNode->getParent()->getRightChild()->getColor()==Black)//Sibling is black, this means we must perform rotations as well as re-colorings.
            {
                if(fixNode->getParent()->getRightChild()->getRightChild()!=NULL&&fixNode->getParent()->getRightChild()->getRightChild()->getColor()==Red)//Single rotation.
                {
                    Node* sibling=fixNode->getParent()->getRightChild();
                    Node* siblingChild=fixNode->getParent()->getRightChild()->getRightChild();
                    sibling->setColor(fixNode->getParent()->getColor());
                    fixNode->getParent()->setColor(Black);
                    siblingChild->setColor(Black);
                    this->rightRightRotate(fixNode->getParent());
                }

                else if(fixNode->getParent()->getRightChild()->getLeftChild()!=NULL&&fixNode->getParent()->getRightChild()->getLeftChild()->getColor()==Red)
                {
                    Node* sibling=fixNode->getParent()->getRightChild();
                    Node* siblingChild=fixNode->getParent()->getRightChild()->getLeftChild();
                    siblingChild->setColor(fixNode->getParent()->getColor());
                    fixNode->getParent()->setColor(Black);
                    sibling->setColor(Black);
                    this->rightLeftRotate(fixNode->getParent());
                }

                else//Both children of sibling are black, which means we must perform re-colorings and potentially move the double black violation up the Red-Black Tree.
                {
                    fixNode->getParent()->getRightChild()->setColor(Red);

                    if(fixNode->getParent()->getColor()==Red)
                    {
                        fixNode->getParent()->setColor(Black);
                    }

                    else
                    {
                        this->removeFixUp(fixNode->getParent());
                    }
                }
            }

            else//Sibling is red, which means that we must rotate and recolor to make new sibling black. This then leads to the previous cases.
            {
                this->rightRightRotate(fixNode->getParent());
                fixNode->getParent()->setColor(Red);
                fixNode->getParent()->getParent()->setColor(Black);//Was old sibling.
                this->removeFixUp(fixNode);
            }
        }

        else if(fixNode->getParent()->getRightChild()==fixNode&&fixNode->getParent()->getLeftChild()!=NULL)//Sibling is parent's left child.
        {
            if(fixNode->getParent()->getLeftChild()->getColor()==Black)////Sibling is black, this means we must perform rotations as well as re-colorings.
            {
                if(fixNode->getParent()->getLeftChild()->getLeftChild()!=NULL&&fixNode->getParent()->getLeftChild()->getLeftChild()->getColor()==Red)//Single Rotation.
                {
                    Node* sibling=fixNode->getParent()->getLeftChild();
                    Node* siblingChild=fixNode->getParent()->getLeftChild()->getLeftChild();
                    sibling->setColor(fixNode->getParent()->getColor());
                    fixNode->getParent()->setColor(Black);
                    siblingChild->setColor(Black);
                    this->leftLeftRotate(fixNode->getParent());
                }

                else if(fixNode->getParent()->getLeftChild()->getRightChild()!=NULL&&fixNode->getParent()->getLeftChild()->getRightChild()->getColor()==Red)
                {
                    Node* sibling=fixNode->getParent()->getLeftChild();
                    Node* siblingChild=fixNode->getParent()->getLeftChild()->getRightChild();
                    siblingChild->setColor(fixNode->getParent()->getColor());
                    fixNode->getParent()->setColor(Black);
                    sibling->setColor(Black);
                    this->leftRightRotate(fixNode->getParent());
                }

                else////Both children of sibling are black, which means we must perform re-colorings and potentially move the double black violation up the Red-Black Tree.
                {
                    fixNode->getParent()->getLeftChild()->setColor(Red);

                    if(fixNode->getParent()->getColor()==Red)
                    {
                        fixNode->getParent()->setColor(Black);
                    }

                    else
                    {
                        this->removeFixUp(fixNode->getParent());
                    }
                }
            }

            else//Sibling is red, which means that we must rotate and recolor to make new sibling black. This then leads to the previous cases.
            {
                this->leftLeftRotate(fixNode->getParent());
                fixNode->getParent()->setColor(Red);
                fixNode->getParent()->getParent()->setColor(Black);//Was old sibling.
                this->removeFixUp(fixNode);
            }
        }

        if(this->getRoot()->getColor()==Red)//This is to make sure that the Red-Black Tree always has a black-colored root Node.
        {
            this->removeFixUp(this->getRoot());
        }
    }
}

void RedBlackTree::clear(Node* clearNode)
{
    if(clearNode!=NULL)
    {
        if(clearNode->getLeftChild()!=NULL)
        {
            this->clear(clearNode->getLeftChild());
        }

        if(clearNode->getRightChild()!=NULL)
        {
            this->clear(clearNode->getRightChild());
        }

        delete clearNode;
        clearNode=NULL;
    }
}

void RedBlackTree::calculateBlackHeight(Node* blackHeightNode)
{
    if(blackHeightNode!=NULL)
    {
        std::srand(time(NULL));

        if(blackHeightNode->getColor()==Black)
        {
            this->setBlackHeight(this->getBlackHeight()+1);
        }

        if(std::rand()%2==0)
        {
            this->calculateBlackHeight(blackHeightNode->getLeftChild());
        }

        else
        {
            this->calculateBlackHeight(blackHeightNode->getRightChild());
        }
    }
}

void RedBlackTree::longestPath(Node* pathNode)
{
    if(pathNode!=NULL)
    {
        std::cout<<"Key: "<<pathNode->getKey()<<" ";

        if(pathNode->getColor()==Black)
        {
            std::cout<<"Color: Black"<<std::endl;
        }

        else
        {
            std::cout<<"Color: Red"<<std::endl;
        }

        if(height(pathNode->getLeftChild())>height(pathNode->getRightChild()))
        {
            this->longestPath(pathNode->getLeftChild());
        }

        else
        {
            this->longestPath(pathNode->getRightChild());
        }
    }
}

int RedBlackTree::height(Node* heightNode)
{
    if(heightNode==NULL)
    {
        return 0;
    }

    else
    {
        return 1+std::max(height(heightNode->getLeftChild()), height(heightNode->getRightChild()));
    }
}

void RedBlackTree::shortestPath(Node* pathNode)
{
    if(pathNode!=NULL)
    {
        std::cout<<"Key: "<<pathNode->getKey()<<" ";

        if(pathNode->getColor()==Black)
        {
            std::cout<<"Color: Black"<<std::endl;
        }

        else
        {
            std::cout<<"Color: Red"<<std::endl;
        }

        if(height(pathNode->getLeftChild())<height(pathNode->getRightChild()))
        {
           this->shortestPath(pathNode->getLeftChild());
        }

        else
        {
            this->shortestPath(pathNode->getRightChild());
        }
    }
}

int RedBlackTree::diameter(Node* diameterNode, int& height)
{
    if(diameterNode==NULL)
    {
        height=0;
        return 0;
    }

    else
    {
        int leftHeight=0;
        int rightHeight=0;

        int leftDiameter=0;
        int rightDiameter=0;

        leftDiameter=diameter(diameterNode->getLeftChild(), leftHeight);
        rightDiameter=diameter(diameterNode->getRightChild(), rightHeight);

        height=std::max(leftHeight, rightHeight)+1;

        return std::max(leftHeight+rightHeight+1, std::max(leftDiameter, rightDiameter));
    }
}

int RedBlackTree::getLeafCount(Node* leafNode)
{
    if(leafNode==NULL)
    {
        return 0;
    }

    else if(leafNode->getLeftChild()==NULL&&leafNode->getRightChild()==NULL)
    {
        return 1;
    }

    else
    {
        return this->getLeafCount(leafNode->getLeftChild())+this->getLeafCount(leafNode->getRightChild());
    }
}

int RedBlackTree::width(Node* widthNode, int depth)
{
    if(widthNode==NULL)
    {
        return 0;
    }

    else if(depth==0)
    {
        return 1;
    }

    else
    {
        return this->width(widthNode->getLeftChild(), depth-1)+this->width(widthNode->getRightChild(), depth-1);
    }

    return -1;
}

void RedBlackTree::printByLevel()
{
    if(this->getRoot()==NULL)
    {
        std::cout<<"There are currently no nodes in the Red-Black Tree to print by level. Please insert a couple of keys in order to print them level by level in the Red-Black Tree later.\n"<<std::endl;
    }

    else
    {
        int maxTreeHeight=this->height(this->getRoot());
        for(int treeLevel=0; treeLevel<maxTreeHeight; treeLevel++)
        {
            std::cout<<"Tree Level: "<<treeLevel<<std::endl;
            this->printLevelOrder(treeLevel, this->getRoot());
            std::cout<<std::endl;
        }
    }
}

void RedBlackTree::printLevelOrder(int treeLevel, Node* levelOrderNode)
{
    if(levelOrderNode!=NULL)
    {
        if(treeLevel==0)
        {
            std::cout<<"Key: "<<levelOrderNode->getKey()<<" ";

            if(levelOrderNode->getColor()==Black)
            {
                std::cout<<"Color: Black"<<std::endl;
            }

            else
            {
                std::cout<<"Color: Red"<<std::endl;
            }
        }

        else
        {
            this->printLevelOrder(treeLevel-1, levelOrderNode->getLeftChild());
            this->printLevelOrder(treeLevel-1, levelOrderNode->getRightChild());
        }
    }
}
