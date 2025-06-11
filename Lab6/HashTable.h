#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>
#include <cmath>



class InterfaceHashFunction {

public:
    virtual ~InterfaceHashFunction() = default;
    virtual size_t hashFunction(int key,size_t tableSize) = 0;

};

class HashFunction1 : public InterfaceHashFunction {

    //int c;
    //int d;
    //int listNumber;
public:
    HashFunction1(){}
    size_t hashFunction(int key,size_t tableSize) override {
        return static_cast<size_t> (key) % tableSize;
    }

};

class HashFunction2 : public InterfaceHashFunction {

    const double a = (sqrt(5) - 1)/2;

public:
    HashFunction2(double aValue) : a(aValue){}
    size_t hashFunction(int key, size_t tableSize) override {
        return static_cast<size_t>(key * a * tableSize) % tableSize;
    }

};

class HashFunction3 : public InterfaceHashFunction {

public:
    size_t hashFunction(int key, size_t tableSize) override {
        return (key % tableSize + (1 + key % (tableSize - 2))) % tableSize;
    }
};

template <typename T>
class HashTable {

public:

    HashTable(size_t tableSize, InterfaceHashFunction* currentFunction, int listNumber);
    HashTable(const HashTable<T>& other);
    ~HashTable();

    void setTableSize(size_t tableSize);
    size_t getTableSize() const;
    const std::vector<std::list<std::pair<int, T>>>& getHashTable() const;
    HashTable<T>& operator=(const HashTable<T>& other);
    void swap(HashTable<T>& other);
    bool contains(int key);
    void insert(int key, T value);
    void removeByKey(int key);
    int keyIndex(int key);
    void deleteByIndex(std::list<std::pair<int, T>>& list, int index);
    void changeHashFunction(InterfaceHashFunction* newFunction);
    const T& operator[](int key) const;

    InterfaceHashFunction* currentFunction = nullptr;

private:

    std::vector<std::list<std::pair<int, T>>> table;
    size_t tableSize = 0;
    //int listNumber = 1;


};

template <typename T>

HashTable<T>::HashTable(size_t tableSize, InterfaceHashFunction* currentFunction)
    : tableSize(tableSize), currentFunction(currentFunction){
    table.resize(tableSize);
}

template <typename T>

HashTable<T>::HashTable(const HashTable& other) : tableSize(other.tableSize), currentFunction(other.currentFunction){}

template <typename T>

HashTable<T>::~HashTable(){
    delete currentFunction;
}

template <typename T>

void HashTable<T>::setTableSize(size_t newSize) {

    if (newSize == tableSize)
        return;

    std::vector<std::list<std::pair<int, T>>> newTable(newSize);

    for (auto it1 = table.begin(); it1 != table.end(); it1++) {
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            size_t hash = currentFunction->hashFunction(it2->first, newSize);
            newTable[hash].push_back(*it2);
        }
    }

    table = newTable;
    tableSize = newSize;
}

template <typename T>

size_t HashTable<T>::getTableSize() const {
    return tableSize;
}

template <typename T>

const std::vector<std::list<std::pair<int, T>>>& HashTable<T>::getHashTable() const {
    return table;
}

template <typename T>

HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other){
    if (this == &other)
        return *this;

    tableSize = other.tableSize;
    table = other.table;
    delete currentFunction;
    currentFunction = other.currentFunction;

    return (*this);
}

template <typename T>

void HashTable<T>::swap(HashTable<T>& other) {
    std::swap(table, other.table);
    std::swap(tableSize, other.tableSize);
    std::swap(currentFunction, other.currentFunction);
}

template <typename T>

bool HashTable<T>::contains(int key){

    if (currentFunction == nullptr) {
        return false;
    }

    size_t hash = currentFunction->hashFunction(key, tableSize);

    for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
        if (it->first == key) {
            return true;
        }
    }
    return false;

}

template <typename T>

void HashTable<T>::insert(int key, T value) {
    if (contains(key))
        return;

    size_t hash = currentFunction->hashFunction(key, tableSize);

    table[hash].push_back(std::pair<int, T>(key, value));
}

template <typename T>

int HashTable<T>::keyIndex(int key){

    size_t hash = currentFunction->hashFunction(key, tableSize);
    int index = 0;

    for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
        index++;
        if (it->first == key) {
            return index;
        }
    }
    return -1;
}


template<typename T>

void HashTable<T>::removeByKey(int key)
{
    int index = keyIndex(key);
    if (index == -1)
        return;

    size_t hash = currentFunction->hashFunction(key, tableSize);

    deleteByIndex(table[hash], index);
}

template<typename T>

void HashTable<T>::deleteByIndex(std::list<std::pair<int, T>>& list, int index){
    if (index >= list.size() || index < 0)
        return;

    typename std::list<std::pair<int, T>>::iterator it = list.begin();
    std::advance(it, index);
    list.erase(it);
}

template <typename T>
void HashTable<T>::changeHashFunction(InterfaceHashFunction* newFunction) {
    if (newFunction == nullptr)
        return;

    std::vector<std::list<std::pair<int, T>>> newTable(tableSize);
    for (auto it1 = table.begin(); it1 != table.end(); it1++) {
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            size_t hash = newFunction->hashFunction(it2->first, tableSize);
            newTable[hash].push_back(*it2);
        }
    }

    delete currentFunction;
    currentFunction = newFunction;
    table = newTable;
}

template <typename T>

const T& HashTable<T>::operator[](int key) const {
    size_t hash = currentFunction->hashFunction(key, tableSize);

    for (auto it = table[hash].begin(); it != table[hash].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }

    std::cerr << "Key not found" << std::endl;
}

template <typename T>

std::ostream& operator<<(std::ostream& os, HashTable<T>& table) {
    for (size_t i = 0; i < table.getTableSize(); i++) {
        os << "hash = " << i << ":\t";

        typename std::list<std::pair<int, T>>::const_iterator it;
        for (it = table.getHashTable()[i].begin(); it != table.getHashTable()[i].end(); it++) {
            os << "key = " << it->first << ", value = " << it->second << " -----> ";
        }
        os << "NULL" << std::endl;
    }
    return os;
}
