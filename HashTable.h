#ifndef HASHTABLE_H
#define HASHTABLE_H

#pragma once
#include "Slot.h"
#include "hashfunction.h"
#include <iostream>

#define MAXHASH 20

class HashTable {
private:
    Slot table[MAXHASH];
    int size;

public:
    HashTable();
    bool insert(int key, int index, int& collisions);
    bool remove(int key);
    bool find(int key, int& index, int& collisions) const;
    float alpha() const;
    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};
#endif //HASHTABLE_H
