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
    
    BinaryTree::Node* getRoot() const;

    bool isEmpty() const;
    int getHeightTree() const;
    virtual int getHeightNode(int key) const;
    int getCountNode() const;
    virtual bool deleteNodeByKey(int key);
    virtual BinaryTree::Node* addNewNode(int key);
    virtual BinaryTree::Node* find(int key) const;
    bool isBalancedTree() const;
    void clearTree();
    void clearSubTree(BinaryTree::Node* node);
    void printByLevel() const;
    virtual std::vector<int> getSortedKeys() ;
    void printTreeHorizontal(int marginLeft, int levelSpacing) const;
    void setRoot(BinaryTree::Node* node);

    virtual int getMinNode() const; 
    virtual int getMaxNode() const; 
    
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other);
    
    BinaryTree::Node* findMostLeft() const;
    BinaryTree::Node* findMostRight() const;
    
    BinaryTree::Node *&getRefRoot ();
    
    protected:
    
    virtual int maxNode(const BinaryTree::Node* node) const;
    virtual int minNode(const BinaryTree::Node* node) const;
    virtual void collectKeys(BinaryTree::Node* node, std::vector<int>& keys);    
    virtual BinaryTree::Node* findNode(BinaryTree::Node* node, int key) const;
    virtual void deleteNode(BinaryTree::Node*& node, int key);
    virtual BinaryTree::Node* addNode(BinaryTree::Node* node, int key);
    virtual int heightNode(Node* root, int key, int level) const;
    
    private:
    
    Node *root = nullptr;    
    BinaryTree::Node* copyTree(const Node* node) const;
    bool isBalanced(BinaryTree::Node* node) const;
    int countNode(const BinaryTree::Node* node) const;
    int heightTree(BinaryTree::Node* node) const;
    void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;
     
};