#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
using namespace std;

class Character {
private:
    string name;
    string role;
    int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;

public:
    // 1.5. Transfer data to character.cpp/Character::Character(string name, string role, int hitPoints, int attackBonus, int damageBonus, int armorClass)
    Character(string name, string role, int hitPoints, int attackBonus, int damageBonus, int armorClass);

    void input();
    void print();
    void attack(Character& them);
    void damage(int amount);
    int getHealth();
    string getName();
    string getRole();

};

#endif
