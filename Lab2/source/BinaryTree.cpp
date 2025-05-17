#include "../include/BinaryTree.h"

BinaryTree::Node::Node() : key(0), left(nullptr), right(nullptr){}

BinaryTree::Node::Node(int key) : key(key), left(nullptr), right(nullptr){}

BinaryTree::Node::Node(int key, Node *left, Node *right) : key(key), left(left), right(right){}

int BinaryTree::Node::getKey() const {
    return key;
}


BinaryTree::Node*& BinaryTree::Node::getRefLeft(){
    return left;
}

BinaryTree::Node*& BinaryTree::Node::getRefRight(){
    return right;
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

void BinaryTree::setRoot(BinaryTree::Node* node){
    root = node;
}


BinaryTree::Node* BinaryTree::getRoot() const{
    return root;
}

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(BinaryTree&& other){

	root = other.getRoot();
	other.setRoot(nullptr);
}

BinaryTree::BinaryTree(const BinaryTree& other){
    root = copyTree(other.root);
}

BinaryTree::~BinaryTree(){
    clearTree();
} 

int BinaryTree::getMinNode() const{
    return minNode(root);
}

int BinaryTree::getMaxNode() const{
    return maxNode(root);
}

int BinaryTree::getHeightNode(int key) const{
    return heightNode(root, key, 1);
}

int BinaryTree::getHeightTree() const{
    return heightTree(root);
}

int BinaryTree::getCountNode() const{
    return countNode(root);
}

void BinaryTree::clearSubTree(BinaryTree::Node* node) {
    if (node == nullptr)
        return;
    clearSubTree(node->getLeft());
    clearSubTree(node->getRight());
    delete node;
}

void BinaryTree::clearTree() {
    if (root != nullptr) {
        clearSubTree(root);
        root = nullptr;
    }
}

int BinaryTree::heightNode(BinaryTree::Node* node, int key, int level) const{
	if (node == nullptr) 
		return -1;

	if (node->getKey() == key)
		return level;

	int left = heightNode(node->getLeft(), key, level + 1);
	if (left != -1)
		return left;

	int right = heightNode(node->getRight(), key, level + 1);
	if (right != -1)
		return right;

    return -1;
}


int BinaryTree::heightTree(BinaryTree::Node* node) const {
    if (node == nullptr)
        return 0;
        
    int leftHeight = heightTree(node -> getLeft());
    int rightHeight = heightTree(node -> getRight());

    if (leftHeight > rightHeight){
        return leftHeight;
    } else {
        return rightHeight;
    }
}



BinaryTree::Node* BinaryTree::copyTree(const BinaryTree::Node* node) const{
    if (node == nullptr){
        return nullptr;
    }
    
    return new Node(node->getKey(), node->getLeft(), node->getRight());
}

bool BinaryTree::isEmpty() const{
    if (root == nullptr)
        return true;

    return false;
}

int BinaryTree::countNode(const BinaryTree::Node* node) const{
    if (node == nullptr)
        return 0;

    return (1 + countNode(node->getLeft()) + countNode(node->getRight()));
}


int BinaryTree::minNode(const BinaryTree::Node* node) const{
    if (node == nullptr){
        return INT32_MAX;
    }
        
    int minLeft = minNode(node->getLeft());
    int minRight = minNode(node->getRight());

    return std::min(node->getKey(), std::min(minLeft, minRight));
}


int BinaryTree::maxNode(const BinaryTree::Node* node) const{
    if (node == nullptr)
        return INT32_MIN;

    int maxLeft  = maxNode(node->getLeft());
    int maxRight  = maxNode(node->getRight());

    return std::max(node->getKey(), std::max(maxLeft, maxRight));
}


BinaryTree::Node* BinaryTree::addNode(BinaryTree::Node* node, int key){
    if (node == nullptr){
        return nullptr;
    } else if (node->getLeft() == nullptr){
        node->setLeft(new BinaryTree::Node(key));
        return node->getLeft();
    } else if (node->getRight() == nullptr){
        node->setRight(new BinaryTree::Node(key));
        return node->getRight();
    } else if (rand() % 2){
        return addNode(node->getLeft(), key);
    } else {
        return addNode(node->getRight(), key);
    }
}

BinaryTree::Node* BinaryTree::addNewNode(int key){
    return addNode(root, key);
}

BinaryTree::Node* BinaryTree::findMostLeft() const {
    if (root== nullptr)
    return nullptr;
    
    
    BinaryTree::Node* node = root;
    while (node && node->getLeft()){
        node = node->getLeft(); 
    }
    return node;
}

BinaryTree::Node* BinaryTree::findMostRight() const {
    if (root== nullptr)
    return nullptr;
    
    
    BinaryTree::Node* node = root;
    while (node && node->getRight()){
        node = node->getRight(); 
    }
    return node;
}

void BinaryTree::deleteNode(BinaryTree::Node*& node, int key){

    if (node == nullptr)
        return;

    if (node->getKey() == key){
        if ((node->getLeft() == nullptr) && (node->getRight() == nullptr)){
            delete node; 
            node = nullptr;
        }
        else if (node->getLeft() == nullptr){
            BinaryTree::Node* temp = node->getRight();
            delete node;
            node = temp;
        } 
        else if (node->getRight() == nullptr){
            BinaryTree::Node* temp = node->getLeft();
            delete node;
            node = temp;
        }
        else {
            if (findNode(root->getLeft(), key)){ 
                
                BinaryTree::Node* mostLeft = findMostLeft();
                int mostLeftKey = mostLeft->getKey();
                deleteNode(node->getRefLeft(), mostLeftKey);
                node->setKey(mostLeftKey);
            } else if (findNode(root->getRight(), key)){
                
                BinaryTree::Node* mostRight = findMostRight();
                int mostRightKey = mostRight->getKey();
                deleteNode(node->getRefRight(), mostRightKey);
                node->setKey(mostRightKey);
            }   
        }
    }
    else { 
        if (findNode(node->getLeft(), key)) {
            deleteNode(node->getRefLeft(), key);
        } else if (findNode(node->getRight(), key)) {
            deleteNode(node->getRefRight(), key);
        }
    }
}

bool BinaryTree::deleteNodeByKey(int key){
   if (root == nullptr)
        return false; 

    deleteNode(root,key);

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
            std::cout << current->getKey() << " ";

            if (current->getLeft()){
                nodes.push_back(current->getLeft());
            }
            
            if (current->getRight()){
                nodes.push_back(current->getRight());
            }
        }
        std::cout << std::endl;
    }  
}

void BinaryTree::printHorizontal(BinaryTree::Node *node, int marginLeft, int levelSpacing) const{
    if (node == nullptr)
        return;

    printHorizontal(node->getLeft(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << node->getKey() << std::endl;
    printHorizontal(node->getRight(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::printTreeHorizontal(int marginLeft, int levelSpacing) const {
    printHorizontal(root, marginLeft, levelSpacing);
}

BinaryTree::Node* BinaryTree::findNode(BinaryTree::Node* node, int key) const{
    if (node == nullptr)
         return nullptr;

    if (node->getKey() == key)
        return node;
    
    BinaryTree::Node* temp = findNode(node->getLeft(), key);
    if (temp != nullptr)
        return temp;
    return findNode(node->getRight(), key);
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
    
    int leftHeight = heightTree(node->getLeft());
    int rightHeight = heightTree(node->getRight());

    return std::abs(leftHeight - rightHeight) <= 1 && isBalanced(node->getLeft()) && isBalanced(node->getRight());
}

bool BinaryTree::isBalancedTree() const{
    return isBalanced(root);
}

void BinaryTree::collectKeys(BinaryTree::Node* node, std::vector<int>& keys) const{
    if (node == nullptr)
        return;
    
    keys.push_back(node->getKey());
    
    collectKeys(node->getLeft(), keys);
    collectKeys(node->getRight(), keys);
}

std::vector<int> BinaryTree::getSortedKeys() const{
    std::vector<int> keys;

    collectKeys(root, keys);

    std::sort(keys.begin(), keys.end());
    
    return keys;
}

