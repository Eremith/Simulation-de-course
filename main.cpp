#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point3D.h"
#include "Runner.h"
#include "Functions.h"

using namespace std;

int main() {

    if (printPath(generatePath(100)) == 1) cout << "erreur kilometrage (10 -> 200)" << endl;

    return 0;
}