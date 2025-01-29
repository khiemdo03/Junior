#include "HashTable.h"
using namespace std;

HashTable::HashTable() : size(0) {} //create an instance of HashTable with the member variable size set to 0. size keeps track of how many slots are occupied in the hash table.

bool HashTable::insert(int key, int index, int& collisions) {
    collisions = 0; //collision counter
    unsigned int hash = jsHash(key) % MAXHASH; //Uses jsHash() to hash the given key and modulo MAXHASH (which is 20)
    unsigned int originalHash = hash; //Stores the initial hash value so we can detect when we loop back to the starting point.

    while (!table[hash].isEmpty()) { //while EmptySlot is not found
        if (table[hash].getKey() == key) { // if the key already exists in the hash table. Return false to prevent duplicate keys.
            return false; // Duplicate key
        }
        //if (table[hash].getKey() != key)
        hash = (hash + 1) % MAXHASH; //Probes the next slot using linear probing. % MAXHASH keeps the index within bounds(20)
        collisions++;  //Increments the collision count each time a filled slot is checked.
        if (hash == originalHash) { // If we return to the original hash value
            return false; // Hash table is full
        }
    }
    //EmptySlot is Found
    table[hash].load(key, index);
    size++; //the size++ of the hash table since a new slot is now occupied.
    return true; //inserted
}

bool HashTable::remove(int key) {
    unsigned int hash = jsHash(key) % MAXHASH;  //Hashes the key to get its index.
    unsigned int originalHash = hash;
    while (!table[hash].isEmptySinceStart()) { //while EmptyAfterRemove and NormalSlot is found
        if (table[hash].isNormal() && table[hash].getKey() == key) {//NormalSlot with matched key is found
            table[hash].kill(); // remove
            size--; //decrement size
            return true; //removed successfully
        }
        //EmptyAfterRemove is found
        hash = (hash + 1) % MAXHASH;
        if (hash == originalHash) {
            return false; // Key not found
        }
    }
    return false;
}
//Comments same thing will lower readability, so refer above :)
bool HashTable::find(int key, int& index, int& collisions) const {
    collisions = 0;
    unsigned int hash = jsHash(key) % MAXHASH;
    unsigned int originalHash = hash;

    while (!table[hash].isEmptySinceStart()) {
        if (table[hash].isNormal() && table[hash].getKey() == key) {
            index = table[hash].getIndex(); //if found, store value to index var
            return true; // if found
        }
        hash = (hash + 1) % MAXHASH;
        collisions++;
        if (hash == originalHash) {
            return false;
        }
    }
    return false;
}

float HashTable::alpha() const {
    return static_cast<float>(size) / MAXHASH; // Computes the load factor by dividing the number of filled slots by the total capacity.
}

ostream& operator<<(std::ostream& os, const HashTable& ht) { //printing of the hash table.
    os << "HashTable contents:" << endl;
    for (int i = 0; i < MAXHASH; i++) {
        if (ht.table[i].isNormal()) { //checks if the slot is in use
            os << "HashTable Slot " << i << ": Key = " << ht.table[i].getKey() << ", Index = " << ht.table[i].getIndex() << std::endl;
        }
    }
    return os;
}
