#ifndef DATABASE_H
#define DATABASE_H

#pragma once
#include "HashTable.h"
#include "Record.h"
#include <vector>
#include <iostream>
using namespace std;

class Database {
private:
    HashTable indexTable;
    vector<Record> recordStore;

public:
    Database();
    bool insert(const Record& newRecord, int& collisions);
    bool remove(int key);
    bool find(int uid, Record& foundRecord, int& collisions);
    float alpha() const;
    friend ostream& operator<<(ostream& os, const Database& db);
};

#endif //DATABASE_H
