#include "BinaryTree.h"
#include <iostream>
#include <string>

int main(){
    
    BinaryTree tree1;
    BinaryTree::Node* node = new BinaryTree::Node(123);
    
    tree1.setRoot(node);
    
    for (int i = 0; i < 100; i++){
        int randNumber = rand() % 100;
        tree1.addNewNode(randNumber);
    }
    
    tree1.printTreeHorizontal(10, 10);
    std::vector<int> keys = tree1.getSortedKeys();
    for(size_t i = 0; i < keys.size(); i++){
    std::cout << keys[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}