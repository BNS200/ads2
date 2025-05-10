#include "BinaryTree.h"
#include <iostream>
#include <string>

int main(){
    BinaryTree tree1;
    BinaryTree tree2;
    BinaryTree::Node* node1 = new BinaryTree::Node(3);
    tree1.setRoot(node1);
    
    tree1.addNewNode(10);
    tree1.addNewNode(18);
    tree1.addNewNode(13);
    tree1.addNewNode(344);
    tree1.addNewNode(95);
    tree1.addNewNode(16);
    tree1.addNewNode(19);
    tree1.addNewNode(100);
    tree1.addNewNode(190);
    tree1.addNewNode(398);

    BinaryTree tree3 = BinaryTree(tree1);


    
    tree1.printTreeHorizontal(20, 20);
    // tree1.printByLevel();
    BinaryTree::Node* findNode = tree1.findMostLeft();
    BinaryTree::Node* nodeRight = node1->getLeft();
    
    std::cout << findNode->getKey() << std::endl;
    std::cout << nodeRight->getKey() << std::endl;
    
    tree1.deleteNodeByKey(18);

   
    tree1.printTreeHorizontal(20, 20);
    

    return 0;
}