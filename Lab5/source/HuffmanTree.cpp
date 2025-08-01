#include "HuffmanTree.h"

HuffmanTree::Node::Node(): frequency(0), left(nullptr), right(nullptr) {} 

void HuffmanTree::Node::setFrequency(int frequencyValue) {
    frequency = frequencyValue;
}

int HuffmanTree::Node::getFrequency() const {
    return frequency;
}

BoolVector HuffmanTree::Node::getSymbols() const {
    return symbols;
}

void HuffmanTree::Node::setSymbols(const BoolVector& symbolsValue) {
    symbols = symbolsValue;
}

HuffmanTree::Node* HuffmanTree::Node::getLeft() const {
    return left;
}

HuffmanTree::Node* HuffmanTree::Node::getRight() const {
    return right;
}

HuffmanTree::Node* HuffmanTree::getRoot() const {
    return m_root;
}

void HuffmanTree::Node::setLeft(Node* leftValue) {
    left = leftValue;
}

void HuffmanTree::Node::setRight(Node* rightValue) {
    right = rightValue;
}

HuffmanTree::Node::~Node() {
    delete left;
    delete right;
}

std::string HuffmanTree::Node::stringifySymbols() const {
    std::string str;
    for (int i = 0; i < symbols.length(); ++i) {
        if (symbols.bitValue(i)) {
            str += static_cast<char>(i);
        }
    }
    return str;
}

void HuffmanTree::Node::printHorizontal(Node* root, int marginLeft, int levelSpacing) const {
    if (root == nullptr) {
        return;
    }
    printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ');
    std::cout << root->getFrequency() << ' ' << root->stringifySymbols();
    std::cout << std::endl;
    printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

void HuffmanTree::clear() {
    clearNode(m_root);
    m_root = nullptr;
}

void HuffmanTree::clearNode(Node* node) { 
    if (node == nullptr)
        return;
    
    clearNode(node->getLeft());   
    clearNode(node->getRight());
    
    delete node;
    node = nullptr;
}

HuffmanTree::~HuffmanTree() {
    clear();
}

void HuffmanTree::print() {
    if (m_root) {
        m_root->printHorizontal(m_root, 0, 10);
    }
}

void HuffmanTree::build(const std::string& fileName) {
    std::string text;

    std::ifstream textFile(fileName);
    if (!textFile.is_open()) {
        std::cerr << "file not open" << std::endl;
        return;
    }

    char textElement;
    while (textFile.get(textElement)) {
        text += textElement;
    }
    textFile.close();

    if (m_root) {
        clear();
    }

    std::vector<Node*> nodes;
    for (const char& symbol : text) {
        std::vector<Node*>::iterator it = std::find_if(nodes.begin(), nodes.end(), 
            [&symbol](Node* node) { // Безымянная функция 
                return node->symbols.bitValue(static_cast<unsigned char>(symbol));
            });

        if (it == nodes.end()) {
            Node* newNode = new Node();
            newNode->setFrequency(1);
            BoolVector boolVector(256, false);
            boolVector.setBitValue(static_cast<unsigned char>(symbol), true);
            newNode->setSymbols(boolVector);
            nodes.push_back(newNode);
        }
        else {
            Node* node = *it;
            node->setFrequency(node->getFrequency() + 1);
        }
    }

    // Ещё одна безымянная функция, сложили в переменную
    auto sorter = [](Node* a, Node* b) -> bool {
        return a->getFrequency() < b->getFrequency();
    };
    std::sort(nodes.begin(), nodes.end(), sorter);

    while (nodes.size() > 1){
        Node *root = new Node();
        root->setFrequency(nodes[0]->getFrequency() + nodes[1]->getFrequency());

        BoolVector boolVector2 = root->getSymbols();
        for (int i = 0; i < root->getSymbols().length(); ++i)
        {
            boolVector2[i] = nodes[0]->getSymbols()[i] || nodes[1]->getSymbols()[i];
        }
        root->setSymbols(boolVector2);

        root->setLeft(nodes[0]);
        root->setRight(nodes[1]);

        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(root);
        std::sort(nodes.begin(), nodes.end(), sorter);
    }
    if (!nodes.empty()) {
        m_root = nodes.front();
    }
}

double HuffmanTree::encode(const std::string& fileName, const std::string& encodedFileName) {
    std::ifstream fileToRead(fileName);
    std::ofstream fileToWrite(encodedFileName);

    if (!fileToRead.is_open() || !fileToWrite.is_open()) {
        std::cerr << "file not open" << std::endl;
        return -1.0;
    }

    if (m_root == nullptr) {
        build(fileName);
        if (m_root == nullptr) {
            return -1.0;
        }
    }

    char symbol;
    std::string encodedText;
    int fileSizeInBits= 0;

    if (!m_root->getLeft() && !m_root->getRight()) {
        while (fileToRead.get(symbol)) {
            fileToWrite << "0";
            fileSizeInBits += 8;
        }
    } else {
        while (fileToRead.get(symbol)) {
            encodedText += encode(m_root, symbol);
            fileSizeInBits += 8;
        }
        fileToWrite << encodedText;
    }

    fileToRead.close();
    fileToWrite.close();

    int compressedSize = encodedText.size(); 
    
    return static_cast<double>(fileSizeInBits) / compressedSize;
}

std::string HuffmanTree::encode(Node* node, char symbol) {
    std::string str;
    
    if (node == nullptr) {
        return str;
    }

    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        return str;
    }

    if (node->getLeft() && node->getLeft()->getSymbols()[symbol]) {
        return "0" + encode(node->getLeft(), symbol);
    }
    else if (node->getRight() && node->getRight()->getSymbols()[symbol]) {
        return "1" + encode(node->getRight(), symbol);
    }

    return str;
}

bool HuffmanTree::decode(const std::string &encodedFile, std::string &decodedFile)
{
    std::ifstream fileToRead(encodedFile);
    std::ofstream fileToWrite(decodedFile);

    if (!fileToRead.is_open() || !fileToWrite.is_open()){
        std::cerr << "file not open" << std::endl;
        return false;
    }

    
    while (fileToRead.good()){
        
        fileToWrite << decode(m_root, fileToRead);
    }
    fileToRead.close();
    fileToWrite.close();
    return true;
}


char HuffmanTree::decode(HuffmanTree::Node* node, std::ifstream &fileToRead)
{
    char symbol;

    if (node->getLeft() == nullptr && node->getRight() == nullptr){
        return node->stringifySymbols()[0];
    }

    fileToRead >> symbol;

    if (symbol == '0'){
        return decode(node->getLeft(), fileToRead);
    } else {
        return decode(node-> getRight(), fileToRead);
    }
    return symbol;
}