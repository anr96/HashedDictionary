#pragma once

#include "DictionaryInterface.h"
#include "HashedEntry.h"
#include <exception>
#include <unordered_map>
#include <vector>


#define DEFAULT_SIZE 101

/**
 *
 * This Hash table is of fixed max size 101 - which is a prime number (why?)
 */
template<class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType> **hashTable;  // Array of pointers to entries
    int itemCount;
    int hashTableSize; //Default value should be assigned to 101

    int getHashIndex(const KeyType &itemKey) const;

    void destroyDictionary();

public:


    virtual ~HashedDictionary();

    HashedDictionary();

    bool isEmpty() const override;

    int getNumberOfItems() const override;

    bool add(const KeyType &searchKey, const ItemType &newItem) override;

    bool remove(const KeyType &searchKey) override;

    void clear() override;

    ItemType getItem(const KeyType &searchKey) const override;

    bool contains(const KeyType &searchKey) const override;

    void traverse(void (*visit)(ItemType &)) const override;

    std::vector<ItemType> toVector() const override;

    HashedEntry<KeyType, ItemType> &operator[](KeyType key);


};

/**
 * DO NOT MODIFY THESE
 */
template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &key) const {
    //DO NOT MODIFY
    return static_cast<int>(key % hashTableSize);
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
        : itemCount(0), hashTableSize(DEFAULT_SIZE) {
    //DO NOT MODIFY
    hashTable = new HashedEntry<KeyType, ItemType> *[DEFAULT_SIZE];
    for (int i = 0; i < DEFAULT_SIZE; i++)
        hashTable[i] = nullptr;
}


template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary() {
    //DO NOT MODIFY
    destroyDictionary();
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear() {
    //DO NOT MODIFY
    destroyDictionary();
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void (*visit)(ItemType &)) const {
    //DO NOT MODIFY
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            visit(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
}

template<class KeyType, class ItemType>
std::vector<ItemType> HashedDictionary<KeyType, ItemType>::toVector() const {
    //DO NOT MODIFY
    std::vector<ItemType> returnVector;
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            returnVector.push_back(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
    return returnVector;
};


template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> &HashedDictionary<KeyType, ItemType>::operator[](KeyType searchKey) {
    //DO NOT MODIFY
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[itemHashIndex];

    // Short circuit evaluation is important here
    while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey())) {
        chainPtr = chainPtr->getNext();
    } // end while

    if (chainPtr == nullptr)
        throw std::exception();

    return *chainPtr;
}

/**
 * DO NOT MODIFY THE ABOVE
 */

/**
 * IMPLEMENT THE REQUIRED BELOW
 */

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::destroyDictionary() {
    for (int i = 0; i < DEFAULT_SIZE; i++)
        if (hashTable[i] != NULL) { //get rid of each item until null
            HashedEntry<KeyType,ItemType> *prevEntry = NULL;
            HashedEntry<KeyType,ItemType> *entry = hashTable[i];
            while (entry != NULL) {
                prevEntry = entry;
                entry = entry->getNext();
                delete prevEntry;
            }
        }
    itemCount = 0; //implied by lack of items in the table
    delete[] hashTable;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const {
    /** Sees whether this dictionary is empty.@return True if the dictionary is empty */
    return itemCount == 0;

}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const {
    /** Gets the number of items in this dictionary. @return The number of items in the dictionary. */
    return itemCount;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem) {
    //Inserts an item into this dictionary according to the item’s search key.
    int hash = getHashIndex(searchKey);

        //insertion when there is nothing at the index
    if (hashTable[hash] == NULL){
        hashTable[hash] = new HashedEntry<KeyType,ItemType>(searchKey,newItem);
        itemCount++;
        return true;
    }


    HashedEntry<KeyType,ItemType>* head = hashTable[hash];
    HashedEntry<KeyType,ItemType>* current = head;
    //already know that it's not empty; insertion at front
    do{
        if(current->getKey()==searchKey){ //searchKey matches
            current->getItem()= newItem;
        }
        current = current->getNext();
    }while(current != nullptr); // exits when reaches last node.


    //Add node to link to the other nodes; at the head of chain
    current=new HashedEntry<KeyType,ItemType>();
    current->setItem(newItem); // set password
    current->setNext(head); // set the next pointer to be the old head.
    hashTable[hash]=current;

    itemCount++;
    return true;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) {
    //Removes an item with the given search key from this dictionary.
    int hash = getHashIndex(searchKey);

    if (hashTable[hash] != NULL && itemCount>1){
        HashedEntry<KeyType,ItemType> *prevEntry = NULL;
        HashedEntry<KeyType,ItemType> *entry = hashTable[hash];
        while (entry->getNext() != NULL && entry->getKey() != searchKey){
            prevEntry = entry;
            entry = entry->getNext();
        }
        if(entry->getKey() == searchKey){
            if (prevEntry == NULL){
                HashedEntry<KeyType,ItemType> *nextEntry = entry->getNext();
                delete entry;
                hashTable[hash] = nextEntry;
            }
            else{
                HashedEntry<KeyType,ItemType> *next = entry->getNext();
                delete entry;
                prevEntry->setNext(next);
            }
        }
        itemCount--;
        return true;
    }
    return false;
}

template<class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const{
    //Retrieves an item with a given search key from a dictionary.
    if(!contains(searchKey) || itemCount<1){
        throw std::exception();
    }

    int hash = getHashIndex(searchKey);
    if (hashTable[hash]) {
        HashedEntry<KeyType, ItemType> *current_element = hashTable[hash];
        while (current_element->getKey() != searchKey && current_element->getNext()) {
            current_element = current_element->getNext();
        }
        return current_element->getItem();
    }
}


template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType &searchKey) const {
    //Sees whether this dictionary contains an item with a given search key.
    int hash = getHashIndex(searchKey);
    if (hashTable[hash]){
        HashedEntry<KeyType, ItemType> *current_element = hashTable[hash];
        while (current_element->getKey() != searchKey && current_element->getNext()){
            current_element = current_element->getNext();
        }
        if (current_element->getKey() == searchKey){
            return true;
        }
    }
    return false;
}


