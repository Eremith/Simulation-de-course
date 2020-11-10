#include <iostream>
#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>

#define sp ";"

using namespace std;

void generatePath(int km){

    srand((unsigned int)time(0));

    ofstream path("path.txt");
    if (path) {

        vector<Point3D> chemin;
        float rpt = 0.4;
        float rptsecond = 0.25;

        Point3D origin(0, 0, 0);
        chemin.insert(chemin.begin(), origin);
        Point3D finish(rand() % (int)km * 2 * rpt - (int)km * rpt, rand() % (int)km * 2 * rpt - (int)km * rpt, km);
        chemin.insert(chemin.end(), finish);

        int count = 0;
        do {
            int distance = 0;
            count = 0;
            int insert = 0;
            for (auto it = chemin.begin(); it != chemin.end() - 1; it++) {
                insert++;
                Point3D t1 = *it;
                Point3D t2 = *(it + 1);
                distance = t2.GetZ() - t1.GetZ();
                if (distance > 10) {
                    Point3D tmp(
                        (t2.GetX() - t1.GetX()) / 2 + (int)(rand() % (t2.GetZ() - t1.GetZ()) * rpt - (t2.GetZ() - t1.GetZ()) * rpt / 2),
                        (t2.GetY() - t1.GetY()) / 2 + (int)(rand() % (t2.GetZ() - t1.GetZ()) * rptsecond - (t2.GetZ() - t1.GetZ()) * rptsecond / 2),
                        (t2.GetZ() - t1.GetZ()) / 2 + t1.GetZ()
                    );
                    chemin.insert(chemin.begin() + insert, tmp);
                    count++;
                    break;
                }
            }
        } while (count > 0);
        
        Point3D end(0, -100, km);
        chemin.insert(chemin.end(), end);
        Point3D start(0, -100, 0);
        chemin.insert(chemin.begin(), start);

        cout << "The vector elements are: ";
        for (auto it = chemin.begin(); it != chemin.end(); ++it) {
            Point3D a = *it;
            path << a.GetX() << sp << a.GetY() << sp << a.GetZ() * 4 << endl;
            cout << a.GetX() << sp << a.GetY() << sp << a.GetZ() * 4 << endl;
        }
        
        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

}

void printPath() {

    vector<Point3D> vPath;

    ofstream path("path.txt");
    if (path) {
        /*
        int count = 0;
        string ligne;
        while (getline(ligne, path)) {

        }
        cout << "Lignes : " << count << endl;
        */
    path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Simulation", sf::Style::Fullscreen);
    sf::CircleShape shape(500.f);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}