#include "BinaryTree.h"
#include <iostream>

class BinaryTreeSearch : public BinaryTree {
    public:
    
        BinaryTreeSearch();
        ~BinaryTreeSearch() = default;
        BinaryTreeSearch(const BinaryTreeSearch& other);
        BinaryTreeSearch(BinaryTreeSearch&& other);

        int getMinNode() const override;
        int getMaxNode() const override;

        BinaryTree::Node* addNewNode(int key) override;

        bool deleteNodeByKey(int key) override;

        BinaryTree::Node* find(int key) const override;

        int getHeightNode(int key) const override;

        std::vector<int> getSortedKeys()  override;

        BinaryTreeSearch& operator=(const BinaryTreeSearch& other);
        BinaryTreeSearch& operator=(BinaryTreeSearch&& other) ;

    private:
        int minNode(BinaryTree::Node* node) const;
        int maxNode(BinaryTree::Node* node) const;

        BinaryTree::Node* addNode(BinaryTree::Node* node, int key); 
        void deleteNode(BinaryTree::Node*& node, int key);
        BinaryTree::Node* findNode(BinaryTree::Node* node, int key) const;
        
        int nodeHeight(BinaryTree::Node* node, int key, int level) const;
        
        void collectKeys(BinaryTree::Node* node, std::vector<int>& keys);
};