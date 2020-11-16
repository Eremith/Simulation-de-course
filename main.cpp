#include <SFML/Graphics.hpp>
#include <iostream>
#include "Class.h"
#include "Functions.h"

using namespace std;

int main() {

    if (generateRunner(10) == 1) {
        cout << "erreur nombre de coureur (2 -> 200)" << endl;
    }
    else {
        InfosRunner *array = readRunner(10);

        //
        cout << "XXXXXXXXXXXXX" << array[0].GetMichel().GetShoesWeight() << endl;
        cout << "XXXXXXXXXXXXX" << array[9].GetMichel().GetShoesWeight() << endl;
        //

        if (generatePath(100) == 1) {
            cout << "erreur kilometrage (10 -> 200)" << endl;
        }
        else {
            printPath(100);
        }
    }

    

    return 0;
}