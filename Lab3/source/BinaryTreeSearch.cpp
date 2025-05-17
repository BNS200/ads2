#include "BinaryTreeSearch.h"
#include "BinaryTree.h"

BinaryTreeSearch::BinaryTreeSearch() : BinaryTree(){};

BinaryTreeSearch::BinaryTreeSearch(const BinaryTreeSearch& other) : BinaryTree(other){};

BinaryTreeSearch::BinaryTreeSearch(BinaryTreeSearch&& other) : BinaryTree(std::move(other)){};

int BinaryTreeSearch::getMinNode() const {
    return minNode(getRoot());
}

int BinaryTreeSearch::getMaxNode() const  {
    return maxNode(getRoot());
}

std::vector<int> BinaryTreeSearch::getSortedKeys(){
    std::vector<int> keys;
    collectKeys(getRoot(), keys);
    return keys;
}

BinaryTree::Node* BinaryTreeSearch::addNewNode(int key)  {
    return addNode(getRoot(), key);
}

bool BinaryTreeSearch::deleteNodeByKey(int key){
    if (getRoot() == nullptr)
        return false;

    deleteNode(getRefRoot(), key);
    return true;
       
}

int BinaryTreeSearch::getHeightNode(int key) const{ 
    return nodeHeight(getRoot(), key, 1);
}

BinaryTree::Node* BinaryTreeSearch::find(int key) const { 
    return findNode(getRoot(), key);
}

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

int BinaryTreeSearch::nodeHeight(BinaryTree::Node* node, int key, int level) const{
    if (node == nullptr){
        return -1;
    }
    
    if (node->getKey() == key)
        return level;
    
    if (node->getKey() < key){
        return nodeHeight(node->getRight(), key, level + 1);
    }
    
    if (node->getKey() > key){
        return nodeHeight(node->getLeft(), key, level + 1);
    }

    return -1;
}

int BinaryTreeSearch::maxNode(BinaryTree::Node* node) const 
{ 
    if (node == nullptr)
        return INT32_MIN;

    while(node != nullptr && node->getRight() != nullptr){
        node = node->getRight();
    }

    return node->getKey();
}

int BinaryTreeSearch::minNode(BinaryTree::Node * node) const
{
    if (node == nullptr)
        return INT32_MAX;

    while(node != nullptr && node->getLeft() != nullptr){
        node = node->getLeft();
    }

    return node->getKey();
}

BinaryTree::Node* BinaryTreeSearch::addNode(BinaryTree::Node* node, int key){
    if (node == nullptr)
        return new BinaryTree::Node(key);
    
    if (getRoot() == nullptr){
        setRoot(new BinaryTree::Node(key));
    }

    if (node->getKey() < key){
        node->setRight(addNode(node->getRight(), key));
    }

    if (node->getKey() > key){
        node->setLeft(addNode(node->getLeft(), key));
    }
    return node;
}

void BinaryTreeSearch::collectKeys(BinaryTree::Node* node, std::vector<int>& keys){
    if (node == nullptr)
        return;
        collectKeys(node->getLeft(), keys);
        keys.push_back(node->getKey());
        collectKeys(node->getRight(), keys);
        
    }