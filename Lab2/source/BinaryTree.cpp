#include "BinaryTree.h"

Node::Node() : key(0), left(nullptr), right(nullptr){}

Node::Node(int key) : key(key), left(nullptr), right(nullptr){}

Node::Node(int key, Node *left, Node *right) : key(key), left(left), right(right){}

int Node::getKey() const {
    return key;
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}

void Node::setKey(int valueKey) {
    key = valueKey;
}

void Node::setLeft(Node *valueLeft) {
    left = valueLeft;
} 

void Node::setRight(Node *valueRight) {
    right = valueRight;
} 

Node* BinaryTree::getRoot() const{
    return root;
}

BinaryTree::BinaryTree() : root(nullptr){}

BinaryTree::~BinaryTree(){
    clear();
} 

void BinaryTree::clearSubTree(Node *node){
    clearSubTree(node->getLeft());
    clearSubTree(node->getRight());
    delete node;

}


void BinaryTree::clear(){
    clearSubTree(root);
    delete root;
    root = nullptr;
}



