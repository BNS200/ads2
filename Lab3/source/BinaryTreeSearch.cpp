#include "BinaryTreeSearch.h"
#include <climits>

BinaryTreeSearch::BinaryTreeSearch() : BinaryTree(){};

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other) : BinaryTree(other){};

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) : BinaryTree(std::move(other)){};

void BinaryTreeSearch::deleteNode(BinaryTree::Node*& node, int key){
    if (node == nullptr)
        return;

    if (node->getKey() == key){
        if ((node->getLeft() == nullptr) &&(node->getRight() == nullptr)){
            delete node;
            node = nullptr;
        } 
        else if ((node->getLeft() == nullptr) && (node->getRight() != nullptr)){
            BinaryTree::Node* temp = node->getRight();
            delete node;
            node = temp;
        } 
        else if ((node->getLeft() != nullptr) && (node->getRight() == nullptr)){
            BinaryTree::Node* temp = node->getLeft();
            delete node;
            node = temp;
        } else if ((node->getLeft() != nullptr) && (node->getRight() != nullptr)){
                int minInLeftSubTree = minNode(node->getRight());
                deleteNodeByKey(minInLeftSubTree);
                node->setKey(minInLeftSubTree);
        } 
    } else {
        if (node->getKey() < key){
            deleteNode(node->getRefRight(), key);
        } else if (node->getKey() > key){
            deleteNode(node->getRefLeft(), key);
        }
    }
}

BinaryTree::Node* BinaryTreeSearch::findNode(BinaryTree::Node* node, int key) const { 
    if(node == nullptr)
        return nullptr;

    if (node->getKey() == key)
        return node;
    if (node->getKey() < key){
        return findNode(node->getRight(), key);
    } else if (node->getKey() > key){
        return findNode(node->getLeft(), key);
    }  
    return nullptr;
}

int BinaryTreeSearch::heightNode(BinaryTree::Node* node, int key, int level) const{
    if (node == nullptr){
        return -1;
    }
    
    if (node->getKey() == key)
        return level;
    
    if (node->getKey() < key){
        return heightNode(node->getRight(), key, level + 1);
    }
    
    if (node->getKey() > key){
        return heightNode(node->getLeft(), key, level + 1);
    }

    return -1;
}

int BinaryTreeSearch::maxNode(const BinaryTree::Node* node) const 
{ 
    if (node == nullptr)
        return INT32_MIN;

    while(node != nullptr && node->getRight() != nullptr){
        node = node->getRight();
    }

    return node->getKey();
}

int BinaryTreeSearch::minNode(const BinaryTree::Node * node) const
{
    if (node == nullptr)
        return INT32_MAX;

    while(node != nullptr && node->getLeft() != nullptr){
        node = node->getLeft();
    }

    return node->getKey();
}

BinaryTree::Node* BinaryTreeSearch::addNode(BinaryTree::Node* node, int key){
    if (getRoot() == nullptr){
        setRoot(new BinaryTree::Node(key));
        return getRoot();
    }
    if (node == nullptr)
        return new BinaryTree::Node(key);

    if (node->getKey() < key){
        node->setRight(addNode(node->getRight(), key));
    }

    if (node->getKey() > key){
        node->setLeft(addNode(node->getLeft(), key));
    }
    return node;
}

void BinaryTreeSearch::collectKeys(BinaryTree::Node* node, std::vector<int>& keys) const {
    if (node == nullptr) {
        return;
    }

    collectKeys(node->getLeft(), keys);
    keys.push_back(node->getKey());
    collectKeys(node->getRight(), keys);
}

BinaryTreeSearch BinaryTreeSearch::optimalTree(const std::vector<int>& keys, const std::vector<int>& p, const std::vector<int>& q) {
    BinaryTreeSearch tree;
    int n = keys.size();

    if (n == 0 || p.size() != n || q.size() != n + 1) {
        return tree;
    }

    std::vector<std::vector<int>> W(n+1, std::vector<int>(n+1, 0));
    std::vector<std::vector<int>> C(n+1, std::vector<int>(n+1, 0));
    std::vector<std::vector<int>> R(n+1, std::vector<int>(n+1, 0));

    for (int i = 0; i <= n; ++i) {
        W[i][i] = q[i];
        C[i][i] = q[i];
    }

    for (int l = 1; l <= n; ++l) {       
        for (int i = 0; i <= n - l; ++i) {
            int j = i + l;                  

            W[i][j] = W[i][j-1] + p[j-1] + q[j];

            C[i][j] = INT_MAX;
            for (int k = i+1; k <= j; ++k) {
                int temp = C[i][k-1] + C[k][j];
                if (temp < C[i][j]) {
                    C[i][j] = temp;
                    R[i][j] = k;
                }
            }
            C[i][j] += W[i][j];
        }
    }


    tree.setRoot(createOptimalTree(keys, R, 0, n));
    return tree;
}

BinaryTree::Node* BinaryTreeSearch::createOptimalTree(const std::vector<int>& keys, const std::vector<std::vector<int>>& R, int i, int j) { 
    if (i >= j) {
        return nullptr;
    }   

    int k = R[i][j];
    BinaryTree::Node* node = new BinaryTree::Node(keys[k-1]);
    node->setRight(createOptimalTree(keys, R, k, j));
    node->setLeft(createOptimalTree(keys, R, i, k-1));

    return node;
}