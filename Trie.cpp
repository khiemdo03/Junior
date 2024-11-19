#include "Trie.h"
#include <iostream>

TrieNode::TrieNode() { //create new Node with 26 nullptr, and set isEndOfWord = false
    isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() { // Create root Node, the father of all
    root = new TrieNode();
    wordCount = 0;
    nodeCount = 1;
}

Trie::~Trie() { //destructor
    clear(root);
}

void Trie::clear(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        clear(node->children[i]);
    }
    delete node;
}

bool Trie::insert(const string& word) { //return T/F if word is inserted
    TrieNode* current = root; //set to root to start, and move to its children by line 37
    for (char x : word) { //undergo all letter in word
        int i = x - 'a'; //take letter minus dec(a) cause it is the first letter
        if (current->children[i] == nullptr) { //if spot in null
            current->children[i] = new TrieNode(); //then create new TrieNode
            nodeCount++;
        }
        current = current->children[i]; //go down to its children
    }
    if (current->isEndOfWord) { //duplicate word
        return false;
    }
    current->isEndOfWord = true; //indicate that the word is new and fully inserted
    wordCount++;
    return true;
}

int Trie::countWord() const {
    return wordCount;
}

int Trie::countNode() const {
    return nodeCount;
}

bool Trie::find(const string& word) const {
    TrieNode* current = root;
    for (char x : word) {
        int i = x - 'a';
        if (current->children[i] == nullptr) {
            return false;
        }
        current = current->children[i];
    }
    return current->isEndOfWord;
}

int Trie::completeCount(const string& prefix) {
    TrieNode* current = root;
    for (char x : prefix) { //check every letter from input
        int i = x - 'a';
        if (current->children[i] == nullptr) { //invalid input
            return 0;
        }
        current = current->children[i]; //go down into last input's letter
    }

    vector<string> results;
    completeHelper(current, prefix, results); //Use this method for the (first) time to Count
    return results.size();
}

vector<string> Trie::complete(const string& prefix)const{
    TrieNode* current = root;
    for (char x : prefix) {
        int i = x - 'a';
        if (current->children[i] == nullptr) {
            return {};
        }
        current = current->children[i];
    }
    vector<string> results;
    completeHelper(current, prefix, results); // Use this method for the (second) time to get the result
    return results;
}

void Trie::completeHelper(TrieNode* node, string prefix, vector<string>& results) const {
    if (node->isEndOfWord) { //when fully word is found, add to result
        results.push_back(prefix);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) { // check next available letter after "prefix"
            completeHelper(node->children[i], prefix + char(i + 'a'), results); //char(i + 'a') to bring back dec number
        }
    }
    //backtracking to the previous position
}

Trie& Trie::operator=(const Trie& other) {
    if (this == &other) {
        return *this; //If the same, it returns *this since there’s no need to perform the assignment.
    }
    //If not the same
    clear(root); //clears all data in the current trie, freeing up memory.
    root = new TrieNode();
    wordCount = 0;
    nodeCount = 1;

    vector<string> words = other.complete(""); // Get all words from other
    for (const string& word : words) {
        insert(word);
    }

    return *this;
}

Trie::Trie(const Trie& other) {
    root = new TrieNode();
    wordCount = 0;
    nodeCount = 1;

    vector<string> words = other.complete(""); // Get all words from other
    for (const string& word : words) {
        insert(word);
    }
}
