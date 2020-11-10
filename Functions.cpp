#include <iostream>
#include "Functions.h"
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
        float rptsecond = 0.1;

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
        
        /*
        int distance = (int)origin.distanceTo(finish);
        if (distance > 10) {
            Point3D tmp(rand() % (int)distance * 2 * rpt - (int)distance * rpt, rand() % (int)distance * 2 * rpt - (int)distance * rpt, (int)finish.GetZ() / 2);
            chemin.insert(chemin.begin() + 1, tmp);
        }
        */
        

        cout << "The vector elements are: ";
        for (auto it = chemin.begin(); it != chemin.end(); ++it) {
            Point3D a = *it;
            path << a.GetX() << sp << a.GetY() << sp << a.GetZ() << endl;
            cout << a.GetX() << sp << a.GetY() << sp << a.GetZ() << endl;
        }
        
        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

}