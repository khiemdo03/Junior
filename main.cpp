/*
Khiem Do
Project 5
Insert and analyze data in a tree imported from file
*/
#include "Trie.h"
#include <iostream>
#include <fstream>

int main() {
    Trie myTrie;
    string filename = "wordlist.txt";
    ifstream infile(filename); //Opens the file filename for reading.

    if (!infile) { //Checks if the file was successfully opened.
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    string word;
    while (infile >> word) { //(>>) mean read each word from the file and stores it in the word variable.
        myTrie.insert(word); //add word into tree
    }
    infile.close(); //good habit, always return the borrowed tool

    cout << "The total word in the trie are " << myTrie.countWord() << endl;
    cout << "The total node in the trie are " << myTrie.countNode() << endl;
    string wordCheck;
    while (true) {
        cout << "What word you want to check if presented in the file?"<<endl;
        getline(cin,wordCheck);
        if (wordCheck.empty()) { //if no input, exit the while loop
            break;
        }
        if(myTrie.find(wordCheck)==1) {
            cout << "The word \"" << wordCheck << "\" is present." << endl;
        }
        else
            cout << "The word \"" << wordCheck << "\" is not present." << endl;
        break;
    }

    string prefix;
    while (true) { //creates an infinite loop that will continue to execute until a break statement is encountered.
        cout << "Please enter a word prefix (or press enter to exit): ";
        getline(cin, prefix);
        if (prefix.empty()) { //if no input, exit the while loop and end program
            break;
        }

        int count = myTrie.completeCount(prefix);
        cout << "There are " << count << " completions for the prefix '" << prefix << "'. Show completions? (yes/no): ";
        string response;
        getline(cin, response);

        if (response == "yes" || response == "Yes") {
            vector<string> completions = myTrie.complete(prefix);
            cout << "Completions\n-----------\n";
            for (const string& print : completions) { //for every result, print.
                cout << print << endl;
            }
        }
        //other than yes, no. Goodbye!
    }
    return 0;
}
