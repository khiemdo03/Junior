#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        string value;
        int height;
        Node* left;
        Node* right;
        Node(int k, const string& v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;

    Node* insert(Node* node, int key, const string& value, bool& inserted);
    Node* balance(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    void inorderPrint(ostream& os, Node* node, int depth) const;
    void deleteTree(Node* node);
    Node* find(Node* node, int key) const;
    void findRange(Node* node, int lowkey, int highkey, vector<string>& result) const;

public:
    AVLTree();
    ~AVLTree();

    bool insert(int key, const string& value);
    int getHeight() const;
    int getSize() const;
    bool find(int key, string& value) const;
    vector<string> findRange(int lowkey, int highkey) const;
    friend ostream& operator<<(ostream& os, const AVLTree& tree);
};

#endif
