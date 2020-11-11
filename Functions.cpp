#include <iostream>
#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <ctime>
#include <cmath>
#include <vector>

#define sp ";"

using namespace std;

int generatePath(int km){

    if (km < 10 || km > 200) return 1;

    srand((unsigned int)time(0));

    ofstream path("path.txt");
    if (path) {

        vector<Point3D> chemin;
        float rpt = 0.5;
        float rptsecond = 0.35;
        int dtcurve = km / 10;

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
                if (distance > dtcurve) {
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
        
        Point3D end(0, 100, km);
        chemin.insert(chemin.end(), end);
        Point3D start(0, 100, 0);
        chemin.insert(chemin.begin(), start);

        //cout << "The vector elements are: ";
        for (auto it = chemin.begin(); it != chemin.end(); ++it) {
            Point3D a = *it;
            path << a.GetX() << sp << a.GetY() << sp << a.GetZ() * 4 << endl;
            //cout << a.GetX() << sp << a.GetY() << sp << a.GetZ() * 4 << endl;
        }
        
        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

    return km;

}

vector<string> split(const string& src, char delim) {
    vector<string> v;
    auto p = begin(src);
    for (auto q = find(p, end(src), delim); q != end(src); q = find(++p, end(src), delim)) {
        v.emplace_back(p, q);
        p = q;
    }
    if (p != end(src))
        v.emplace_back(p, end(src));
    return v;
}

int printPath(int km) {

    if (km == 1) return 1;

    vector<Point3D> vPath;
    sf::ConvexShape convex;
    sf::VertexArray lines(sf::LineStrip);

    ifstream path("path.txt");
    if (path) {
        
        int count = 0;
        string ligne;
        while (getline(path, ligne)) {
            count++;
        }

        lines.resize(count);
        convex.setPointCount(count);

        path.clear();
        path.seekg(0, ios::beg);

        int current = 0;
        while (getline(path, ligne)) {
            vector<string> n = split(ligne, ';');
            int x = atoi(n[0].c_str()), y = atoi(n[1].c_str()), z = atoi(n[2].c_str());
            
            cout << x << " " << y << " " << z << endl;

            convex.setPoint(current, sf::Vector2f(z * (int)(800 / (km * 4)), y));
            lines[current].position = sf::Vector2f(z * (int)(800 / (km * 4)), x * (int)(800 / (km * 4)) + 600);

            current++;
        }

        lines.resize(count - 1);

        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;



    
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Simulation");
    int screen_width = (sf::VideoMode::getDesktopMode().width - 1500) / 2;
    int screen_height = (sf::VideoMode::getDesktopMode().height - 800) / 2;
    window.setPosition(sf::Vector2i(screen_width, screen_height));

    convex.setPosition(0, 200);
    convex.setFillColor(sf::Color(0, 125, 0));
    

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(convex);
        window.draw(lines);
        window.display();
    }

    return 0;
    
}