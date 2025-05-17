#include "BinaryTree.h"
#include <iostream>

class BinaryTreeSearch : public BinaryTree {
    public:
    
        BinaryTreeSearch();
        ~BinaryTreeSearch() = default;
        BinaryTreeSearch(const BinaryTreeSearch& other);
        BinaryTreeSearch(BinaryTreeSearch&& other);

        BinaryTreeSearch& operator=(const BinaryTreeSearch& other);
        BinaryTreeSearch& operator=(BinaryTreeSearch&& other) ;

    protected:
        int minNode(BinaryTree::Node* node) const override;
        int maxNode(BinaryTree::Node* node) const override;

        BinaryTree::Node* addNode(BinaryTree::Node* node, int key) override; 
        void deleteNode(BinaryTree::Node*& node, int key) override;
        BinaryTree::Node* findNode(BinaryTree::Node* node, int key) const override;
        
        int nodeHeight(BinaryTree::Node* node, int key, int level) const override;
        
        void collectKeys(BinaryTree::Node* node, std::vector<int>& keys) override;
};