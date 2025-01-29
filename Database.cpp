#include "Database.h"
using namespace std;

Database::Database() {}

bool Database::insert(const Record& newRecord, int& collisions) {
    int uid = newRecord.getUID(); //get uid from Record.h
    int index;
    collisions = 0;

    // Check if the record already exists
    if (indexTable.find(uid, index, collisions)) {
        return false; // Duplicate UID found
    }

    // Insert record into recordStore
    recordStore.push_back(newRecord);
    int recordIndex = recordStore.size() - 1;

    // Insert UID and index into hash table
    if (!indexTable.insert(uid, recordIndex, collisions)) {
        return false; // Hash table is full or other issue
    }
    return true;
}

bool Database::remove(int key) {
    int index;
    int collisions = 0;

    // Find the record in the hash table
    if (!indexTable.find(key, index, collisions)) {
        return false; // Record not found
    }

    // Remove from hash table
    if (!indexTable.remove(key)) {
        return false; // Failed to remove from hash table
    }

    // Remove from recordStore without wasting memory
    recordStore[index] = recordStore.back();
    recordStore.pop_back();

    // Update the moved record's index in hash table, if necessary
    if (index < recordStore.size()) {
        int movedUID = recordStore[index].getUID();
        int dummyCollisions;
        indexTable.insert(movedUID, index, dummyCollisions);
    }

    return true;
}

bool Database::find(int uid, Record& foundRecord, int& collisions) {
    int index;
    collisions = 0;

    // Find the record in the hash table
    if (!indexTable.find(uid, index, collisions)) {
        return false; // Record not found
    }

    // Get the record from the recordStore
    foundRecord = recordStore[index];
    return true;
}

float Database::alpha() const {
    return indexTable.alpha();
}

ostream& operator<<(ostream& os, const Database& db) {
    os << "Database contents:" << endl;
    for (int i = 0; i < db.recordStore.size(); ++i) {
        int uid = db.recordStore[i].getUID();
        int index;
        int collisions = 0;
        db.indexTable.find(uid, index, collisions);
        os << "HashTable Slot: " << index << ", recordStore slot " << i << " -- " << db.recordStore[i] << endl;
    }
    return os;
}
