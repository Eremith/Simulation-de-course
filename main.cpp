#include <SFML/Graphics.hpp>
#include <iostream>
#include "Class.h"
#include "Functions.h"

#define RUNNER 100
#define KM 40

using namespace std;

int main() {

    if (generateRunner(RUNNER) == 1) {
        cout << "erreur nombre de coureur (2 -> 200)" << endl;
    }
    else {
        InfosRunner *array = readRunner(RUNNER);

        if (generatePath(KM) == 1) {
            cout << "erreur kilometrage (10 -> 100)" << endl;
        }
        else {
            sf::ConvexShape al;
            sf::VertexArray am(sf::LinesStrip);
            readPath(KM, &al, &am);
            printPath(al, am, array, RUNNER, KM);
        }
    }

    return 0;
}