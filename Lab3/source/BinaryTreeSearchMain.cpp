#include "BinaryTreeSearch.h"

int main() { 
    BinaryTreeSearch tree1;
    for (size_t i = 0; i < 30; i++)
    {
        int randValue = rand() % 101;
        tree1.addNewNode(randValue);
    }

    
    tree1.printTreeHorizontal(10, 10);
    return 0;
}
