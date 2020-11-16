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
        float rpt = 0.3;
        float rptsecond = 0.3;
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

        for (auto it = chemin.begin(); it != chemin.end(); ++it) {
            Point3D a = *it;
            path << a.GetX() * 4 << sp << a.GetY() << sp << a.GetZ() * (int)(800 / km) << endl;
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

            //
            cout << x << " " << y << " " << z << endl;
            //

            convex.setPoint(current, sf::Vector2f(z, y));
            lines[current].position = sf::Vector2f(z, x + 600);

            current++;
        }

        lines.resize(count - 1);

        //
        for (int i = 1; i < convex.getPointCount() - 2; i++) {
            float pente = 0;
            pente = (convex.getPoint(i).y - convex.getPoint(i + 1).y * 100) / sqrt(pow(abs((lines[i].position.y - 600) - (lines[i + 1].position.y - 600)), 2) + pow(abs(convex.getPoint(i).y - convex.getPoint(i + 1).y), 2) + pow(abs(convex.getPoint(i).x - convex.getPoint(i + 1).x), 2));
            cout << pente << endl;
            if (pente - (int)pente > 0.5) {
                pente = (int)pente + 1;
            }
            else {
                pente = (int)pente;
            }
            cout << pente << endl;
        }
        //

        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;



    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Simulation");

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

int generateRunner(int nbrunner) {

    if (nbrunner < 2 || nbrunner > 200) return 1;

    ofstream runner("runner.txt");
    if (runner) {

        srand((unsigned int)time(0));

        for (int i = 0; i < nbrunner; i++) {
            int poids = rand() % 75 + 45;
            float taille = (rand() % 70 + 130) / 100.;
            int shoes = rand() % 200 + 100;
            float vtprec = (rand() % 130 + 70) / 10.;
            int prepa = rand() % 8 + 8;

            int dossard = i + 1;

            runner << poids << sp << taille << sp << shoes << sp << vtprec << sp << prepa << sp << dossard << endl;
        }

        runner.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

    return nbrunner;
}

InfosRunner *readRunner(int nbrunner) {

    ifstream runner("runner.txt");
    if (runner) {
        
        int count = 0;
        InfosRunner* array = new InfosRunner[nbrunner];
        string ligne;
        while (getline(runner, ligne)) {
            vector<string> n = split(ligne, ';');
            int poids = atoi(n[0].c_str()), shoes = atoi(n[2].c_str()), prepa = atoi(n[4].c_str()), dossard = atoi(n[5].c_str());
            float taille = atof(n[1].c_str()), vtprec = atof(n[3].c_str());

            //
            cout << poids << sp << taille << sp << shoes << sp << vtprec << sp << prepa << sp << dossard << endl;
            //

            Runner rene(poids, taille, shoes, vtprec, prepa, dossard);
            
            float v = 0;
            int w = 0;
            InfosRunner b(rene, v, w, w);
            array[count] = b;

            count++;
        }
        runner.close();

        return array;
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;
}