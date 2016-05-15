#pragma  once


#include "Entry.h"

template<class KeyType, class ItemType>
class HashedEntry : public Entry<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType> *nextPtr;

public:
    HashedEntry();

    HashedEntry(KeyType searchKey, ItemType newEntry);

    HashedEntry(KeyType searchKey, ItemType newEntry,
                HashedEntry<KeyType, ItemType> *nextEntryPtr);

    void setNext(HashedEntry<KeyType, ItemType> *nextEntryPtr);

    HashedEntry<KeyType, ItemType> *getNext() const;

    void operator=(const ItemType&);
};

// Implement the necessary functions

template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>::HashedEntry() { }


template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>::HashedEntry(KeyType searchKey, ItemType newEntry){
    Entry<KeyType,ItemType>::setKey(searchKey);
    Entry<KeyType,ItemType>::setItem(newEntry);
    setNext(nullptr);
}


template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>::HashedEntry(KeyType searchKey, ItemType newEntry, HashedEntry *nextEntryPtr){
    Entry<KeyType,ItemType>::setKey(searchKey);
    Entry<KeyType,ItemType>::setItem(newEntry);
    setNext(nextEntryPtr);
}


template<class KeyType, class ItemType>
void HashedEntry<KeyType,ItemType>::setNext(HashedEntry *nextEntryPtr) {
    nextPtr = nextEntryPtr;
}

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType> *HashedEntry<KeyType, ItemType>::getNext() const {
    return nextPtr;
}


template<class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::operator=(const ItemType& newItem){
    //DO
    this->setItem(newItem);

};

