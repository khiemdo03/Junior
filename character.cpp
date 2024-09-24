#include "character.h"
#include <iostream>
#include <cstdlib>  // for rand()
using namespace std;

// 3. Fill data to private in character.h
Character::Character(string name, string role, int hitPoints, int attackBonus, int damageBonus, int armorClass)
    : name(name), role(role), hitPoints(hitPoints), attackBonus(attackBonus), damageBonus(damageBonus), armorClass(armorClass) {
}

void Character::input() {
    cout << " Character name? ";
    cin >> name;
    cout << name <<"'s role? ";
    cin >> role;
    cout << name << " the " << role << "'s hit points? ";
    cin >> hitPoints;
    cout << name << " the " << role << "'s attack bonus? ";
    cin >> attackBonus;
    cout << name << " the " << role << "'s damage bonus? ";
    cin >> damageBonus;
    cout << name << " the " << role << "'s armor class? ";
    cin >> armorClass;
}


void Character::print() {
    cout << " " << name << " the " << role << "\n";
    cout << " HP: " << hitPoints << "\n";
    cout << " AB: " << attackBonus << "\n";
    cout << " DB: " << damageBonus << "\n";
    cout << " AC: " << armorClass << "\n";
}

void Character::attack(Character& opponent) { // attack(& means address of Character-type opponent)
    // Roll a 20-sided die, or generate a random number 1 to 20
    //Determine of HIT or MISS
    int attackRoll = (rand() % 20) + 1;
    cout << name << " attacks!\n";
    cout << "Attack roll: " << attackRoll << " + " << attackBonus << " = " << attackRoll + attackBonus;

    // HIT
    if (attackRoll + attackBonus >= opponent.armorClass) {
        cout << " --> HIT!\n";
        // Calculate for Damage to HIT
        int randomDmg = (rand() % 10) + 1;
        int totalDamage = randomDmg + damageBonus;
        cout << "Damage: " << randomDmg << " + " << damageBonus << " = " << totalDamage << "\n";
        opponent.damage(totalDamage);
    }
    //MISS
    else {
        cout << " --> MISS!" << endl << endl;
    }
}

void Character::damage(int dmg) {
    hitPoints -= dmg;    // hitPoints = hitPoints - amount
    if (hitPoints < 0) {
        hitPoints = 0;
        cout << name << " has " << hitPoints << " hit points remaining" << endl << endl;
    }
    else {
        cout << name << " has " << hitPoints << " hit points remaining" << endl << endl;
    }
}

//getHealth is hitPoints
int Character::getHealth() {
    return hitPoints;
}

string Character::getName() {
    return name;
}

string Character::getRole() {
    return role;
}

