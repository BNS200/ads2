#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class BinaryTree {
    public:
    class Node {
    public:
        Node();
        Node(int key);
        Node(int key, Node *left, Node *right);
        
        ~Node() = default;

        int getKey() const;
        void setKey(int valueKey);
    
        Node *getLeft() const;
        Node *getRight() const;

        Node*& getRefLeft();
        Node*& getRefRight();

        void setLeft(Node *valueLeft);
        void setRight(Node *valueRight);
        
    private:
        Node *left = nullptr;
        Node *right = nullptr;
        int key = 0;
    };
    
    public:
    
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other);
    

    bool isEmpty() const;
    BinaryTree::Node* getRoot() const;
    int getHeightTree() const;
    int getHeightNode(int key) const;
    int getCountNode() const;
    bool deleteNodeByKey(int key);
    BinaryTree::Node* addNewNode(int key);
    BinaryTree::Node* find(int key) const;
    bool isBalancedTree() const;
    void clearTree();
    void clearSubTree(BinaryTree::Node* node);
    void printByLevel() const;
    std::vector<int> getSortedKeys() const;
    void printTreeHorizontal(int marginLeft, int levelSpacing) const;
    void setRoot(BinaryTree::Node* node);

    int getMinNode() const;
    int getMaxNode() const;
    
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other);
    
    BinaryTree::Node* findMostLeft() const;
    BinaryTree::Node* findMostRight() const;
    
    private:
    
    Node *root = nullptr;    
    int maxNode(const BinaryTree::Node* node) const;
    int minNode(const BinaryTree::Node* node) const;
    BinaryTree::Node* findNode(BinaryTree::Node* node, int key) const;
    BinaryTree::Node* copyTree(const Node* node) const;
    bool isBalanced(BinaryTree::Node* node) const;
    void deleteNode(BinaryTree::Node*& node, int key);
    int heightNode(Node* root, int key, int level) const;
    int countNode(const BinaryTree::Node* node) const;
    int heightTree(BinaryTree::Node* node) const;
    void collectKeys(BinaryTree::Node* node, std::vector<int>& keys) const;    
    BinaryTree::Node* addNode(BinaryTree::Node* node, int key);
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;

};