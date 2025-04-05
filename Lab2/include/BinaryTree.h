#pragma once
#include <iostream>



class Node {

public:
    Node();
    Node(int key);
    Node(int key, Node *left, Node *right);

    int getKey() const;
    void setKey(int valueKey);

    Node *getLeft() const;
    Node *getRight() const;

    void setLeft(Node *valueLeft);
    void setRight(Node *valueRight);
    

private:
    int key = 0;
    Node *left = nullptr;
    Node *right = nullptr;

};

class BinaryTree {

public:
    BinaryTree();
    ~BinaryTree();
    void clear();
    Node *getRoot() const;
    void clearSubTree(Node *node);
private:
    Node *root = nullptr;    

};