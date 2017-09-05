#include<sstream>
#include"RedBlackTree.h"

int main()
{
    std::cout<<"Welcome to the Red-Black Tree manipulator.\n"<<std::endl;
    std::cout<<"Before starting, an empty Red-Black Tree will be created for you to manipulate.\n"<<std::endl;
    RedBlackTree* RBT=new RedBlackTree();

    std::cout<<"Now that the Red-Black Tree has been created, a menu will now be printed describing the various ways one can manipulate the Red-Black Tree.\n"<<std::endl;
    std::cout<<"1. Insert a key/a set of keys into the Red-Black Tree."<<std::endl;
    std::cout<<"2. View all the keys currently in the Red-Black Tree in non-decreasing order."<<std::endl;
    std::cout<<"3. Search for a key/a set of keys in the Red-Black Tree."<<std::endl;
    std::cout<<"4. Remove a key/a set of keys from the Red-Black Tree."<<std::endl;
    std::cout<<"5. View the current amount of nodes in the Red-Black Tree."<<std::endl;
    std::cout<<"6. View the current black-height of the Red-Black Tree."<<std::endl;
    std::cout<<"7. View all the keys in the longest path of the Red-Black Tree."<<std::endl;
    std::cout<<"8. View all the keys in the shortest path of the Red-Black Tree."<<std::endl;
    std::cout<<"9. View the current diameter of the Red-Black Tree."<<std::endl;
    std::cout<<"10. View the current number of leaf nodes in the Red-Black Tree."<<std::endl;
    std::cout<<"11. View the current width of the Red-Black Tree."<<std::endl;
    std::cout<<"12. Print all the nodes in the Red-Black Tree in level-order."<<std::endl;
    std::cout<<"13. Clear the Red-Black Tree for the insertion of a new set/new sets of keys."<<std::endl;
    std::cout<<"14. Quit the Red-Black Tree manipulator program.\n"<<std::endl;
    std::cout<<"Now you will enter your desired choice by entering the number associated with its description.\n"<<std::endl;

    std::string menuChoice=std::string();
    std::getline(std::cin, menuChoice);
    std::cout<<std::endl;
    std::stringstream menuChoiceSS(menuChoice);
    int menuChoice2=0;
    menuChoiceSS>>menuChoice2;
    while(menuChoice2!=14)
    {
        switch(menuChoice2)
        {
            case 1:
            {
                std::cout<<"Now please enter the key(s) that you would like to insert into the Red-Black Tree.\n"<<std::endl;
                std::string keysInsert=std::string();
                std::getline(std::cin, keysInsert);
                std::cout<<std::endl;

                std::stringstream keysInsertSS(keysInsert);
                while(keysInsertSS>>keysInsert)
                {
                    int key=0;
                    std::stringstream keysInsertSS2(keysInsert);
                    keysInsertSS2>>key;
                    RBT->insertKey(key, RBT->getRoot());
                }

                break;
            }

            case 2:
            {
                std::cout<<"Now the key(s) currently in the Red-Black Tree will be printed in non-decreasing order.\n"<<std::endl;
                RBT->printInOrder(RBT->getRoot());
                std::cout<<std::endl;

                break;
            }

            case 3:
            {
                std::cout<<"Now please enter the key(s) that you would like to search for in the Red-Black Tree.\n"<<std::endl;
                std::string keysSearch=std::string();
                std::getline(std::cin, keysSearch);
                std::cout<<std::endl;

                std::stringstream keysSearchSS(keysSearch);
                while(keysSearchSS>>keysSearch)
                {
                    int key=0;
                    std::stringstream keysSearchSS2(keysSearch);
                    keysSearchSS2>>key;
                    RBT->searchKey(key, RBT->getRoot());
                }

                break;
            }

            case 4:
            {
                std::cout<<"Now please enter the key(s) that you would like to remove from the Red-Black Tree.\n"<<std::endl;
                std::string keysRemove=std::string();
                std::getline(std::cin, keysRemove);
                std::cout<<std::endl;

                std::stringstream keysRemoveSS(keysRemove);
                while(keysRemoveSS>>keysRemove)
                {
                    int key=0;
                    std::stringstream keysRemoveSS2(keysRemove);
                    keysRemoveSS2>>key;
                    RBT->removeKey(key, RBT->getRoot());
                }

                break;
            }

            case 5:
            {
                std::cout<<"There is/are "<<RBT->getNumberOfNodes()<<" node(s) in the Red-Black Tree.\n"<<std::endl;

                break;
            }

            case 6:
            {
                RBT->setBlackHeight(0);
                RBT->calculateBlackHeight(RBT->getRoot());
                std::cout<<"The current black-height of the Red-Black Tree is "<<RBT->getBlackHeight()<<".\n"<<std::endl;

                break;
            }

            case 7:
            {
                std::cout<<"The node(s) on the longest path will now be shown.\n"<<std::endl;
                std::cout<<"The node(s) on the longest path is/are:\n"<<std::endl;
                RBT->longestPath(RBT->getRoot());
                std::cout<<std::endl;

                break;
            }

            case 8:
            {
                std::cout<<"The node(s) on the shortest path will now be shown.\n"<<std::endl;
                std::cout<<"The node(s) on the shortest path is/are:\n"<<std::endl;
                RBT->shortestPath(RBT->getRoot());
                std::cout<<std::endl;

                break;
            }

            case 9:
            {
                std::cout<<"Now the diameter of the Red-Black Tree will be calculated.\n"<<std::endl;
                int height=0;
                std::cout<<"The diameter of the Red-Black Tree is/are "<<RBT->diameter(RBT->getRoot(), height)<<" node unit(s).\n"<<std::endl;

                break;
            }

            case 10:
            {
                std::cout<<"Now the leaf node count of the Red-Black Tree will be calculated.\n"<<std::endl;
                std::cout<<"There is/are "<<RBT->getLeafCount(RBT->getRoot())<<" leaf node(s) in the Red-Black Tree.\n"<<std::endl;

                break;
            }

            case 11:
            {
                std::cout<<"Now the width of the Red-Black Tree will be calculated.\n"<<std::endl;
                int maxWidth=0;
                int temp=0;
                for(int depth=0; depth<=RBT->height(RBT->getRoot()); depth++)
                {
                    temp=RBT->width(RBT->getRoot(), depth);

                    if(temp>maxWidth)
                    {
                        maxWidth=temp;
                    }
                }

                std::cout<<"The width of the Red-Black Tree is "<<maxWidth<<" node(s) wide.\n"<<std::endl;

                break;
            }

            case 12:
            {
                std::cout<<"Now all the nodes of the Red Black Tree will be printed in level-order.\n"<<std::endl;
                RBT->printByLevel();

                break;
            }

            case 13:
            {
                std::cout<<"Now the Red-Black Tree will be cleared.\n"<<std::endl;
                delete RBT;
                RBT=NULL;
                RBT=new RedBlackTree();
                std::cout<<"The Red-Black Tree has successfully been cleared for the insertion of a new set/new sets of keys.\n"<<std::endl;

                break;
            }

            default:
            {
                break;
            }
        }

        std::cout<<"For reminder purposes, a menu will now be displayed describing the various ways one can manipulate the Red-Black Tree.\n"<<std::endl;
        std::cout<<"1. Insert a key/a set of keys into the Red-Black Tree."<<std::endl;
        std::cout<<"2. View all the keys currently in the Red-Black Tree in non-decreasing order."<<std::endl;
        std::cout<<"3. Search for a key/a set of keys in the Red-Black Tree."<<std::endl;
        std::cout<<"4. Remove a key/a set of keys from the Red-Black Tree."<<std::endl;
        std::cout<<"5. View the current amount of nodes in the Red-Black Tree."<<std::endl;
        std::cout<<"6. View the current black-height of the Red-Black Tree."<<std::endl;
        std::cout<<"7. View all the keys in the longest path of the Red-Black Tree."<<std::endl;
        std::cout<<"8. View all the keys in the shortest path of the Red-Black Tree."<<std::endl;
        std::cout<<"9. View the current diameter of the Red-Black Tree."<<std::endl;
        std::cout<<"10. View the current number of leaf nodes in the Red-Black Tree."<<std::endl;
        std::cout<<"11. View the current width of the Red-Black Tree."<<std::endl;
        std::cout<<"12. Print all the nodes in the Red-Black Tree in level-order."<<std::endl;
        std::cout<<"13. Clear the Red-Black Tree for the insertion of a new set/new sets of keys."<<std::endl;
        std::cout<<"14. Quit the Red-Black Tree manipulator program.\n"<<std::endl;

        std::cout<<"Please enter your next choice of operation on the Red-Black Tree by entering the number associated with its description.\n"<<std::endl;
        std::getline(std::cin, menuChoice);
        std::cout<<std::endl;
        menuChoiceSS.str(std::string());
        menuChoiceSS.clear();
        menuChoiceSS<<menuChoice;
        menuChoiceSS>>menuChoice2;
    }

    delete RBT;
    RBT=NULL;

    return 0;
}
