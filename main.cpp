/*
 * Project 6
 * Khiem Do
 * Real-life database programming
 */
//ps: Jon, I am quite tired to write code explanation for this main, so forgive me. Thank you for being my TA for this semester. I wish you have a wonderful break.
#include "Database.h"
#include <iostream>

using namespace std;

int main() {
    Database db;
    int collisions;
    char choice;

    while (true) {
        cout << "\nWould you like to (I)nsert, (D)elete, (S)earch, (P)rint the database, or (Q)uit?\nEnter action: ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'I') {
            string firstName, lastName, year;
            int uid;
            cout << "Inserting a new record.\n";
            cout << "Last name: ";
            cin >> lastName;
            cout << "First name: ";
            cin >> firstName;
            cout << "UID: ";
            cin >> uid;
            cout << "Year: ";
            cin >> year;

            Record newRecord(firstName, lastName, uid, year);
            if (db.insert(newRecord, collisions)) {
                cout << "Record inserted (" << collisions << " collisions during insert)." << endl;
            } else {
                cout << "Failed to insert record. Duplicate UID or hash table full." << endl;
            }

        } else if (choice == 'D') {
            int uid;
            cout << "Enter UID to delete: ";
            cin >> uid;
            if (db.remove(uid)) {
                cout << "Record deleted." << endl;
            } else {
                cout << "Record not found." << endl;
            }

        } else if (choice == 'S') {
            int uid;
            Record foundRecord;
            cout << "Enter UID to search for: ";
            cin >> uid;
            if (db.find(uid, foundRecord, collisions)) {
                cout << "Searching... record found (" << collisions << " collisions during search)" << endl;
                cout << "----------------------------" << endl;
                cout << foundRecord << endl;
                cout << "----------------------------" << endl;
            } else {
                cout << "Searching... record not found" << endl;
            }

        } else if (choice == 'P') {
            cout << db;

        } else if (choice == 'Q') {
            cout << "Exiting." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
