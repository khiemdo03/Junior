#include "AVLTree.h"

// Constructor
AVLTree::AVLTree() : root(nullptr), size(0) {} //Create AVLTree Constructor with (root)=nullptr (meaning empty tree) and (size)=zero.

// Destructor calls deleteTree(node) to murder each child in the tree
AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
    if (node) { //if node is not nullptr
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// to return if node is inserted. Call insert method to insert or check.
bool AVLTree::insert(int key, const string& value) {
    bool inserted = false;
    root = insert(root, key, value, inserted); //call insert method
    if (inserted) //successfully inserted aka inserted = true
        size++; // increment size by 1
    return inserted;
}

// insert method with balancing
AVLTree::Node* AVLTree::insert(Node* node, int key, const string& value, bool& inserted) {
    if (!node) { // if node = null, then insert to the EMPTY tree
        inserted = true;
        return new Node(key, value);
    }
    if (key < node->key) { //if key(data) is smaller than this node. Go to left
        node->left = insert(node->left, key, value, inserted);
    }
    else if (key > node->key) { // if key(data) is larger than this node. Go to right
        node->right = insert(node->right, key, value, inserted);
    }
    else { // if duplicate key
        inserted = false; //false because I do not want to increment the size (which is only when inserted = true)
        return node;
    }
    //calculate the height of new node by 1(current node height) +  max(biggest number between both)
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return balance(node);
}

// Get the height of the node
int AVLTree::getHeight(Node* node) const {
    if (node) { //if node is not null
        return node->height;
    } //if node is null
        return -1;
}

int AVLTree::getHeight() const {
    return getHeight(root);
}

// Get the balance factor of the node by minus node on the right by node on the left
int AVLTree::getBalanceFactor(Node* node) const {
    return getHeight(node->left) - getHeight(node->right);
}

// Balance the AVL tree
AVLTree::Node* AVLTree::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) { // adjust by rotating to the left
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (balanceFactor < -1) { // adjust by rotating to the right
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node; // balanced
}

// Rotate tree to the left
AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right; //newRoot = 50->right = 100
    node->right = newRoot->left; //100 = 100->left = null
    newRoot->left = node; //null = 50
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}
// Rotate tree to the rigth
AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    return newRoot;
}

// More rotations for balancing
AVLTree::Node* AVLTree::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLTree::Node* AVLTree::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Get the size of the tree
int AVLTree::getSize() const {
    return size;
}

// Overload << operator to print the tree sideways
ostream& operator<<(ostream& os, const AVLTree& tree) {
    tree.inorderPrint(os, tree.root, 0);
    return os;
}

//Hey Jon, this code was suggest by claude.ai, print from the end of right subtree, to root, to left subtree
void AVLTree::inorderPrint(ostream& os, Node* node, int depth) const {
    if (node) {
        inorderPrint(os, node->right, depth + 1);
        os << string(depth * 8, ' ') << node->key << ", " << node->value << endl;
        inorderPrint(os, node->left, depth + 1);
    }
}

// Find a node with the given key
bool AVLTree::find(int key, string& value) const {
    Node* node = find(root, key);
    if (node) {
        value = node->value;
        return true;
    }
    return false;
}

AVLTree::Node* AVLTree::find(Node* node, int key) const {
    if (!node) //find null
        return nullptr;
    if (key < node->key) // fill node smaller than curren key
        return find(node->left, key);
    if (key > node->key) // find node larger than current key
        return find(node->right, key);
    //successfully found
    return node;
}

// Find the range of keys between lowkey and highkey
vector<string> AVLTree::findRange(int lowkey, int highkey) const {
    vector<string> result;
    findRange(root, lowkey, highkey, result);
    return result;
}
// run all way to the end then check and add as going back up
void AVLTree::findRange(Node* node, int lowkey, int highkey, vector<string>& result) const {
    if (!node) // if null, meaning leaf
        return;
    if (lowkey < node->key) // given node smaller than current key
        findRange(node->left, lowkey, highkey, result); //
    if (lowkey <= node->key && node->key <= highkey)
        result.push_back(node->value); //add this node to result vector
    if (highkey > node->key)
        findRange(node->right, lowkey, highkey, result);
}
