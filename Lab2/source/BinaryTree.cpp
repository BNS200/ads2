#include "BinaryTree.h"

BinaryTree::Node::Node() : key(0), left(nullptr), right(nullptr){}

BinaryTree::Node::Node(int key) : key(key), left(nullptr), right(nullptr){}

BinaryTree::Node::Node(int key, Node *left, Node *right) : key(key), left(left), right(right){}

int BinaryTree::Node::getKey() const {
    return key;
}

BinaryTree::Node* BinaryTree::Node::getLeft() const {
    return left;
}

BinaryTree::Node* BinaryTree::Node::getRight() const {
    return right;
}

void BinaryTree::Node::setKey(int valueKey) {
    key = valueKey;
}

void BinaryTree::Node::setLeft(Node *valueLeft) {
    left = valueLeft;
} 

void BinaryTree::Node::setRight(Node *valueRight) {
    right = valueRight;
} 

BinaryTree::Node* BinaryTree::getRoot() const{
    return root;
}

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(BinaryTree&& other) : root(other.root) {}

void BinaryTree::clearTree(){
    clearSubTree(root);
    root = nullptr;
}

void BinaryTree::clearSubTree(BinaryTree::Node* node){
    if (node == nullptr)
        return;
    clearSubTree(node -> left);
    clearSubTree(node -> right);
    delete node;
}

BinaryTree::~BinaryTree(){
    clearTree();
} 

int BinaryTree::getHeight(BinaryTree::Node* node) const {
    if (node == nullptr)
        return 0;
        
    int leftHeight = getHeight(node -> left);
    int rightHeight = getHeight(node -> right);

    if (leftHeight > rightHeight){
        return leftHeight;
    } else {
        return rightHeight;
    }
}

BinaryTree::BinaryTree(const BinaryTree& other){
    root = copyTree(other.root);
}

BinaryTree::Node* BinaryTree::copyTree(const BinaryTree::Node* node) const{
    if (node == nullptr){
        return nullptr;
    }
    
    return new Node(node->getKey(), node->getLeft(), node->getRight());
}

bool BinaryTree::isEmpty() const{
    if (root == nullptr)
        return false;

    return true;
}

int BinaryTree::countNode(const BinaryTree::Node* node) const{
    if (node == nullptr)
        return 0;

    return (1 + countNode(node->left) + countNode(node->right));
}

int BinaryTree::minNode(const BinaryTree::Node* node) const{
    if (node == nullptr){
        return 0;
    }
        
    int minLeft = minNode(node->left);
    int minRight = minNode(node->right);

    return std::min(node->key, std::min(minLeft, minRight));
}

int BinaryTree::maxNode(const BinaryTree::Node* node) const{
    if (node == nullptr)
        return 0;

    int maxLeft  = maxNode(node->left);
    int maxRight  = maxNode(node->right);

    return std::max(node->key, std::max(maxLeft, maxRight));
}

BinaryTree::Node* BinaryTree::addNode(BinaryTree::Node* node, int key){
    if (node == nullptr){
        return nullptr;
    } else if (node->left == nullptr){
        node->setLeft(new BinaryTree::Node(key));
        return node->left;
    } else if (node->right == nullptr){
        node->setRight(new BinaryTree::Node(key));
        return node->right;
    } else if (rand() % 2){
        return addNode(node->left, key);
    } else {
        return addNode(node->right, key);
    }
}

BinaryTree::Node* BinaryTree::findMostRight(BinaryTree::Node* node) const {
    if (node == nullptr)
        return nullptr;
    
    while (node && node->right){
        node = node->right; 
    }
    return node;
}

BinaryTree::Node* BinaryTree::deleteNode(BinaryTree::Node* node, int key){
    if (node == nullptr)
        return nullptr;

    if (node->key == key){
        if ((node->left == nullptr) && (node->right == nullptr)){
            delete node; 
            node = nullptr;
            return node;
        }
        else if (node->left == nullptr){
            delete node;
            return node = node->right;
        } 
        else if (node->right == nullptr){
            delete node;
            return node = node->left;
        }
        else {
            BinaryTree::Node* temp = findMostRight(node);
            delete node; 
            return node = temp;
        }
        
    }
    return nullptr;
}

bool BinaryTree::deleteNodeByKey(int key){
    BinaryTree::Node* node = deleteNode(root, key);
    if (node == nullptr)
        return false;
 
    return true;    
}

void BinaryTree::printByLevel() const{
    std::vector<Node*> nodes;
    nodes.push_back(root);
    
    while (!nodes.empty()){
        int levelSize = nodes.size();

        for (size_t i = 0; i < levelSize; i++){
            BinaryTree::Node* current  = nodes.front();
            nodes.pop_back();
            std::cout << current -> key << " ";

            if (current->getLeft()){
                nodes.push_back(current->left);
            }
            
            if (current->getRight()){
                nodes.push_back(current->right);
            }
        }
        std::cout << std::endl;
    }  
}

void BinaryTree::printHorizontal(BinaryTree::Node *node, int marginLeft, int levelSpacing) const{
    if (node == nullptr)
        return;

    printHorizontal(node->left, marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << node->key << std::endl;
    printHorizontal(node->right, marginLeft + levelSpacing, levelSpacing);
}

BinaryTree::Node* BinaryTree::findNode(BinaryTree::Node* node, int key) const{
    if (node == nullptr)
         return nullptr;
    if (node->key == key)
        return node;
    BinaryTree::Node* newNode  = findNode(node->left, key);
    if (node)
        return node;
    return findNode(node->right, key);
}

BinaryTree::Node* BinaryTree::find(int key) const{
    return findNode(root, key);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other){
    if (this != &other){
        clearTree();
        root = copyTree(other.root);
    }
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other){
    if (this != &other){
        clearTree();
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

bool BinaryTree::isBalanced(BinaryTree::Node* node) const{
    if (node == nullptr)
     return false;
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return std::abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

bool BinaryTree::isBalancedTree() const{
    return isBalanced(root);
}

void BinaryTree::collectKeys(BinaryTree::Node* node, std::vector<int>& keys) const{
    if (node == nullptr)
        return;
    
    keys.push_back(node->key);
    
    collectKeys(node->left, keys);
    collectKeys(node->right, keys);
}

std::vector<int> BinaryTree::getSortedKeys() const{
    std::vector<int> keys;

    collectKeys(root, keys);

    std::sort(keys.begin(), keys.end());
    
    return keys;
}

