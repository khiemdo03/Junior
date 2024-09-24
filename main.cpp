// -----------------------------
//Khiem Do
// Project 2
// Fighting between 2 characters
//------------------------------

#include <iostream>
#include "character.h"
using namespace std;

int main() {
    string name, role;
    int hitPoints, attackBonus, damageBonus, armorClass;

    // 1.Create a Character-type named one with 6 values
    //Call class Character
    Character one(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    // 2.Call Character::input()
    one.input();
    cout << "\n Character summary\n";
    cout << " -----------------\n";
    // 3. Call character.cpp/void Character::print()
    one.print();

    // 4. Repeat 1,2,3 for second time
    Character two(name, role, hitPoints, attackBonus, damageBonus, armorClass);
    two.input();
    cout << "\n Character summary\n";
    cout << " -----------------\n";
    two.print();


    // 5. Combat simulation
    cout << "\nSimulated Combat:\n";
    while (one.getHealth() > 0 && two.getHealth() > 0) {
        //one's turn to attack
        one.attack(two);
        if (one.getHealth() <= 0) {
            cout << two.getName() << " wins!\n";
            break;
        }
        //two's turn to attack
        two.attack(one);
        if (one.getHealth() <= 0) {
            cout << two.getName() << " wins!\n";
        }
    }
    return 0;
}
