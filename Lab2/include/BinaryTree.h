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
    
        void setLeft(Node *valueLeft);
        void setRight(Node *valueRight);
        
    
        int key = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    
    };
    
    public:
    
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other);
    

    bool isEmpty() const;
    BinaryTree::Node* copyTree(const Node* node) const;
    BinaryTree::Node* getRoot() const;
    int getHeight(BinaryTree::Node* node) const;
    int countNode(const BinaryTree::Node* node) const;
    int maxNode(const BinaryTree::Node* node) const;
    int minNode(const BinaryTree::Node* node) const;
    BinaryTree::Node* addNode(BinaryTree::Node* node, int key);
    BinaryTree::Node* deleteNode(BinaryTree::Node* node, int key);
    bool deleteNodeByKey(int key);
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;
    BinaryTree::Node* findNode(BinaryTree::Node* node, int key) const;
    BinaryTree::Node* find(int key) const;
    bool isBalanced(BinaryTree::Node* node) const;
    bool isBalancedTree() const;
    void clearTree();
    void clearSubTree(BinaryTree::Node* node);
    BinaryTree::Node* findMostRight(BinaryTree::Node* node) const;
    void printByLevel() const;
    void collectKeys(BinaryTree::Node* node, std::vector<int>& keys) const;    
    std::vector<int> getSortedKeys() const;


    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other);


    private:
    Node *root = nullptr;    

};