// -----------------------------
//Khiem Do 
// Project 1
// Frenquency of dices roll into particular sum from (2..12)
//------------------------------

#include <iostream>  //input, output
#include <cstdlib>   //rand(), srand()
#include <ctime>     //time() to seed srand()

using namespace std; //to not write again lol

int main() {

    int input;  //to ask for input from user

    srand(time(nullptr)); //generate seconds in time => pass to srand to generate rand

    cout << "How many rolls: ";
    cin >> input; // take input from keyboard

    int allSum[11] = {0}; //array named allSum that hold 11 values. 11 because dice[1] + dice[2] = [2...12] 
                            // {0} means set all elements inside array = 0
//====Simulator====
    for (int i = 0; i < input; i++) { //Roll "input" times
        int dice1 = rand() % 6 + 1; // Remainder of (random number / 6) + 1. To keep [1..6]
        int dice2 = rand() % 6 + 1; 
        int sum = dice1 + dice2;    // dice1 + dice2

        allSum[sum - 2]++; //Ex: if sum = 12, allNum at index[12-2=10] increment by 1
    }

//====Result====
    cout << "Simulating " << input << " rolls..." << endl << "Result: \n";
    for (int i = 0; i < 11; i++) {                      //Run through array (index 0 -10)
        cout << (i + 2) << " was rolled " << allSum[i] << " times\n"; //(i + 2) because index 0 hold value 2, index 1 hold value 3, so on... 
                                            //allSum[i] return value it is holding.
    }

    return 0;
}

