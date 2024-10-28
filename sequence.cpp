// -----------------------------
//Khiem Do
// Project 3
// Use doubly linked list to manipulate node in a list
//------------------------------
#include "Sequence.h"

///@brief Insert new node (element) into the sequence by calling push_back method for every elements
Sequence::Sequence(size_type sz) : head(nullptr), tail(nullptr), numElts(0)
{
    for (size_type i = 0; i < sz; ++i) {
        push_back(value_type());
    }
}

/// @brief
Sequence::Sequence(const Sequence& s) : head(nullptr), tail(nullptr), numElts(0)
{
    SequenceNode* temp = s.head; //Start at the beginning(head) of sequence
    while (temp != nullptr) { // head != null
        push_back(temp->elt);  // Copy each element
        temp = temp->next;
    }
    //head = null. STOP
}

Sequence::~Sequence()
{
clear();
}

Sequence& Sequence::operator=(const Sequence& s)
{
    if (this != &s) {
        clear();  // Clear existing list
        SequenceNode* current = s.head;
        while (current != nullptr) {
            push_back(current->elt);  // Copy each element
            current = current->next;
        }
    }
    return *this;
}

Sequence::value_type& Sequence::operator[](size_type position)
{
    if (position >= numElts) {
        throw out_of_range("There is no such position");  // Out of bounds
    }
    SequenceNode* current = head;
    for (size_type i = 0; i < position; ++i) {
        current = current->next;
    }
    return current->elt;
}

void Sequence::push_back(const value_type& value)
{
    SequenceNode* temp = new SequenceNode(value);
    if (tail) { //tail is true, there is tail
        tail->next = temp; // next ptr of tail point to temp
        temp->prev = tail; // prev ptr of temp point to tail
    }
    else {  // tail is false, no tail
        head = temp;
    }
    tail = temp; // tail always point to temp when new node is added because added at the end of the sequence
    ++numElts; // incre number of Element or new node by 1
}

void Sequence::pop_back()
{
    if (numElts == 0) {
        throw underflow_error("Sequence is empty, cannot pop");  //underflow_error for an empty sequence
        }
    SequenceNode* toDelete = tail; // initialize new pointer toDelete to tail
    if (tail->prev) { //if these is node before tail
        tail = tail->prev; // that previous node will be tail
        tail->next = nullptr;// point next pointer to null to pop
    }
    else // no node before tail aka one node
    {
        head = nullptr;  // set both head and tail to null to pop
        tail = nullptr;
    }
    delete toDelete;
    --numElts;
}

void Sequence::insert(size_type position, value_type value)
{
    if (position > numElts) {
        throw exception();  // Out of bounds
    }
    SequenceNode* newNode = new SequenceNode(value);
    if (position == 0) { //assign newNode as first node
        newNode->next = head;   //next pointer of newNode point to head, indicate that newNode stay before head
        if (head) // if there is head
            head->prev = newNode; //head's prev pointer point to newNode, indicate that newNode stay front
            head = newNode;     // set head to newNode, indicate that head now is newNode
        if (numElts == 0) tail = newNode;  // Empty list case
    }
    else { //assign newNode at other places
        SequenceNode* current = head; //create a pointer point at head
        for (size_type i = 0; i < position - 1; ++i) { //
            current = current->next; //loop, or run all the way to destined position
        }
        newNode->next = current->next; // new node next = current next
        newNode->prev = current;    // newNode prev point back current
        if (current->next) // if there is next, indicate not yet tail
            current->next->prev = newNode; //
        current->next = newNode;
        if (position == numElts) tail = newNode;  // Insert at the end
    }
    ++numElts;
}

const Sequence::value_type& Sequence::front() const
{
    if (empty()) {
        throw exception();
    }
    return head->elt;
}

const Sequence::value_type& Sequence::back() const {
    if (empty()) {
        throw out_of_range("Index out of bounds");  //out_of_range
    }
    return tail->elt;
}

bool Sequence::empty() const
{
    return numElts == 0;
}

Sequence::size_type Sequence::size() const
{
    return numElts;
}

void Sequence::clear()
{
    while (!empty()) {
        pop_back();
    }
}

void Sequence::erase(size_type position) {
    if (position >= numElts) {
        throw exception();  // Out of bounds
    }
    SequenceNode* toDelete = head;
    for (size_type i = 0; i < position; ++i) {
        toDelete = toDelete->next;
    }
    if (toDelete->prev) toDelete->prev->next = toDelete->next;
    else head = toDelete->next;  // Deleting the head
    if (toDelete->next) toDelete->next->prev = toDelete->prev;
    else tail = toDelete->prev;  // Deleting the tail
    delete toDelete;
    --numElts;
}

void Sequence::erase(size_type position, size_type count)
{
    if (position + count > numElts) {
        throw exception();  // Out of bounds
    }
    for (size_type i = 0; i < count; ++i) {
        erase(position);  // Keep erasing at the position, as elements shift
    }
}

// Place code for printing sequence here (well not here, inside the method)
void Sequence::print(ostream& os) const
{
    SequenceNode* current = head;
    os << "<";
    while (current != nullptr) {
        os << current->elt;
        if (current->next != nullptr) os << ", ";
        current = current->next;
    }
    os << ">";
}

// Don't modify, do the output in the print() method
ostream& operator<<(ostream& os, const Sequence& s)
{
    s.print(os);
    return os;
}

