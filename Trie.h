#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26]; // array of 26 pointers cause a-z
    bool isEndOfWord;

    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    int wordCount;
    int nodeCount;

    void completeHelper(TrieNode* node, string prefix, vector<string>& results) const;

public:
    Trie();
    ~Trie();
    bool insert(const string& word); //insert from file's words to trie
    int countWord() const; //count total word
    int countNode() const;// count total node
    bool find(const string& word) const;
    int completeCount(const string& prefix);
    vector<string> complete(const string& prefix) const;
    Trie& operator=(const Trie& other); //ensure no memory leak
    Trie(const Trie& other); // Copy constructor

    void clear(TrieNode* node);
};

#endif
