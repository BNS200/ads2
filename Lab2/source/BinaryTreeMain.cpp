#include "BinaryTree.h"
#include <iostream>
#include <string>

int main(){
    BinaryTree tree1;
    BinaryTree::Node* node1 = new BinaryTree::Node(10);
    tree1.setRoot(node1);

    
    // BinaryTree::Node* temp1 = tree1.find(5);
    // if (temp1 != nullptr){
    //     std::cout << "temp != nullptr" << std::endl;    
    // } else {
    //     std::cout << "temp == nullptr" << std::endl;
    // }

    tree1.addNewNode(5);
    tree1.addNewNode(5);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(1);
    tree1.addNewNode(5);
    tree1.addNewNode(5);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(10);
    tree1.addNewNode(1);
   

    // BinaryTree::Node* temp2 = tree1.find(5);
    // if (temp2 != nullptr){
    //     std::cout << "temp != nullptr" << std::endl;    
    // } else {
    //     std::cout << "temp == nullptr" << std::endl;
    // }

    // tree1.addNewNode(5);
    // tree1.addNewNode(13);
    // tree1.addNewNode(344);
    // tree1.addNewNode(95);
    // tree1.addNewNode(16);
    // tree1.addNewNode(19);
    
    // tree1.addNewNode(100);
    // tree1.addNewNode(190);
    // tree1.addNewNode(398);
    
    tree1.printTreeHorizontal(1, 10);
    // BinaryTree::Node* findNode = tree1.findMostLeft();
    // BinaryTree::Node* nodeRight = node1->getLeft();
    
    // std::cout << findNode->getKey() << std::endl;
    // std::cout << nodeRight->getKey() << std::endl;
    
    
    
    
    
    // tree1.deleteNodeByKey(5);
    // tree1.deleteNodeByKey(5);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    tree1.deleteNodeByKey(1);
    // tree1.deleteNodeByKey(5);
    // tree1.deleteNodeByKey(5);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    // tree1.deleteNodeByKey(10);
    tree1.deleteNodeByKey(5);
    tree1.deleteNodeByKey(1);
    
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
    tree1.printTreeHorizontal(1, 10);
    

    return 0;
}