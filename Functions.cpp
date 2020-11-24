#include <iostream>
#include "Functions.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <vector>
#include <iomanip>

#define sp ";"

using namespace std;

int generatePath(int km){

    if (km < 10 || km > 100) return 1;

    srand((unsigned int)time(0));

    ofstream path("path.txt");
    if (path) {

        vector<Point3D> chemin;
        float rpt = 0.3;
        float rptsecond = 0.3;
        int dtcurve = 5;

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
                if (distance >= dtcurve) {
                    Point3D tmp(
                        (t2.GetX() - t1.GetX()) / 2 + (int)(rand() % (t2.GetZ() - t1.GetZ()) * rpt - (t2.GetZ() - t1.GetZ()) * rpt / 2) + rand() % 8 - 2,
                        (t2.GetY() - t1.GetY()) / 2 + (int)(rand() % (t2.GetZ() - t1.GetZ()) * rptsecond - (t2.GetZ() - t1.GetZ()) * rptsecond / 2) + rand() % 8 - 2,
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

int readPath(int km, sf::ConvexShape *c, sf::VertexArray *l) {

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

        *c = convex;
        *l = lines;

        path.close();
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;

    return 0;
    
}

int printPath(sf::ConvexShape convex, sf::VertexArray lines, InfosRunner* array, int nb, int km) {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Simulation");

    convex.setPosition(0, 200);
    convex.setFillColor(sf::Color(0, 125, 0));

    sf::Text text[20];
    sf::Font font;
    if (!font.loadFromFile("OpenSans-Bold.ttf"))
    {
        // erreur...
    }
    for (int h = 0; h < nb; h++) {
        text[h].setFont(font);
        text[h].setString("");
        text[h].setColor(sf::Color::White);
        text[h].setCharacterSize(24);
        text[h].setPosition(1000, 50 + 20 * h);
    }
    sf::Text time;
    time.setFont(font);
    time.setString("a");
    time.setColor(sf::Color::White);
    time.setCharacterSize(24);
    time.setPosition(50, 50);

    sf::CircleShape gens(3);
    vector<pair<sf::CircleShape, pair<InfosRunner, int>>> gehghghns(nb);

    for (int i = 0; i < nb; i++) {
        gehghghns[i].first = gens;
        gehghghns[i].first.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        gehghghns[i].second.second = 1;
        gehghghns[i].second.first = array[i];
    }

    vector<float> distanceBetweenPoints(convex.getPointCount() - 2);
    for (int i = 0; i < convex.getPointCount() - 3; i++) {
        distanceBetweenPoints[i] = (km * 5 / 4) * sqrt(pow(lines[i + 2].position.y - lines[i + 1].position.y, 2) + pow(convex.getPoint(i + 2).y - convex.getPoint(i + 1).y, 2) + pow(convex.getPoint(i + 2).x - convex.getPoint(i + 1).x, 2));
        cout << distanceBetweenPoints[i] << sp; //en m
    }
    cout << endl;

    float distance = 0;
    for (int v = 0; v < convex.getPointCount() - 3; v++) {
        distance += distanceBetweenPoints[v];
    }

    vector<InfosRunner> leaderboard(10);

    int i = 0;
    int endc = 1;
    while (window.isOpen()) {

        sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            float tmpdistance = 0;
            if (endc <= nb) {
                


                for (int k = 0; k < nb; k++) { //Calcul de la VInst, de la distance parcourue et du point précédent
                    float vinst = 0;
                    if (gehghghns[k].second.first.GetTraveled() >= distance) {
                        vinst = 0;
                    }
                    else {
                        vinst = gehghghns[k].second.first.GetMichel().GetAvgSpeed() / 3.6; //vitesse par défaut en m/s
                    }

                    int a = gehghghns[k].second.second;
                    float pente = -((convex.getPoint(a + 1).y - convex.getPoint(a).y) * 100) / sqrt(pow(lines[a + 1].position.y - lines[a].position.y, 2) + pow(convex.getPoint(a + 1).y - convex.getPoint(a).y, 2) + pow(convex.getPoint(a + 1).x - convex.getPoint(a).x, 2));
                    if (pente < 0) { //vitesse selon la pente
                        vinst = vinst * (1 + pente / 150); //pente descendante
                    }
                    else {
                        vinst = vinst * (1 + 0.35 * (-pente / 150)); //pente montante
                    }

                    int c = gehghghns[k].second.first.GetMichel().GetShoesWeight() / 100;
                    vinst = vinst * (1 - (c * 1.1) / 100); //vitesse selon poids chaussure

                    //vitesse decroissante selon training
                    float slow = 42.195 / (2 * (1 + (gehghghns[k].second.first.GetMichel().GetTraining() - 8.) / 8));
                    if (slow < gehghghns[k].second.first.GetTraveled() / 1000) {
                        float rpt = ((gehghghns[k].second.first.GetTraveled() / 1000) - slow) / 100;
                        if (rpt >= 0.20) {
                            rpt = 0.20;
                        }
                        vinst = vinst * (1 - rpt);
                    }

                    gehghghns[k].second.first.SetVinst(vinst); //vinst = m/s, avgspeed = km/h
                    gehghghns[k].second.first.SetTraveled(gehghghns[k].second.first.GetTraveled() + gehghghns[k].second.first.GetVinst()); //traveled = m, vinst = m/s

                    //

                    struct compA {
                        bool operator()(pair<sf::CircleShape, pair<InfosRunner, int>>& a1, pair<sf::CircleShape, pair<InfosRunner, int>>& a2)
                        {
                            return (a1.second.first.GetTraveled() < a2.second.first.GetTraveled());
                        }
                    };


                    std::sort(gehghghns.begin() + endc - 1, gehghghns.end(), compA());
                    std::reverse(gehghghns.begin() + endc - 1, gehghghns.end());


                    for (int d = 0; d < nb; d++) {
                        ostringstream oss;
                        int entier = (int)(gehghghns[d].second.first.GetVinst() * 100.0);
                        float fltvinst = (float)entier / 100;
                        entier = (int)(gehghghns[d].second.first.GetTraveled() / 100);
                        float flttraveled = (float)entier / 10;
                        oss << d + 1 << " " << gehghghns[d].second.first.GetPrenom() << "   " << fltvinst << "   " << flttraveled;
                        std::string result = oss.str();
                        text[d].setString(result);
                    }
                    //

                    tmpdistance = 0; //en m
                    for (int v = 0; v < convex.getPointCount() - 3; v++) {
                        tmpdistance += distanceBetweenPoints[v];
                        if (gehghghns[k].second.first.GetTraveled() >= tmpdistance) gehghghns[k].second.second = v + 1;
                    }
                    float tmpd = 0; // en m
                    for (int f = 0; f < gehghghns[k].second.second; f++) {
                        tmpd += distanceBetweenPoints[f];
                    }
                    float tmpx = 0, tmpy = 0; // en m
                    float tmpdst = (gehghghns[k].second.first.GetTraveled() - tmpd) / distanceBetweenPoints[gehghghns[k].second.second]; // en m
                    tmpx = tmpdst * (convex.getPoint(gehghghns[k].second.second + 2).x * ((km * 5) / 4) - convex.getPoint(gehghghns[k].second.second + 1).x * ((km * 5) / 4)) + convex.getPoint(gehghghns[k].second.second + 1).x * ((km * 5) / 4);
                    tmpy = tmpdst * (convex.getPoint(gehghghns[k].second.second + 2).y * ((km * 5) / 4) - convex.getPoint(gehghghns[k].second.second + 1).y * ((km * 5) / 4)) + convex.getPoint(gehghghns[k].second.second + 1).y * ((km * 5) / 4);
                    tmpx = (tmpx * 4) / (km * 5); //en px
                    tmpy = (tmpy * 4) / (km * 5); // en px
                    gehghghns[k].first.setPosition(tmpx - 3, tmpy + 197);
                }   //traveled en m, tmpd en m, distanceBetweenPoints en m, convexgetpoint x et y en px

                endc = 1;
                for (int n = 0; n < nb; n++) {
                    if (gehghghns[n].second.first.GetTraveled() >= tmpdistance) {
                        endc++;
                    }
                }
                i++;

                ostringstream oss;
                int heure = i / 3600;
                int minute = (i % 3600) / 60;
                int seconde = i % 60;
                oss << "Durée de la course : " << heure << "h" << minute << "min" << seconde << "s";
                std::string result = oss.str();
                time.setString(result);
            }
            

            window.clear();
            window.draw(convex);

            for (int k = 0; k < nb; k++) {
                window.draw(gehghghns[k].first);
            }

            for (int k = 0; k < nb; k++) {
                window.draw(text[k]);
            }

            window.draw(time);

            window.draw(lines);
            window.display();
    }
    cout << "ITERATION (=secondes)" << i << endl;

    return 0;

}

int generateRunner(int nbrunner) {

    if (nbrunner < 2 || nbrunner > 200) return 1;

    ofstream runner("runner.txt");
    if (runner) {

        srand((unsigned int)time(0));

        for (int i = 0; i < nbrunner; i++) {
            int poids = rand() % 75 + 45;
            float taille = (rand() % 70 + 130.) / 100.;
            int shoes = rand() % 200 + 100;
            float vtprec = (rand() % 130 + 70.) / 10.;


            int prepa = rand() % 8 + 8;

            int dossard = i + 1;

            string tab[] = { "Jean", "Pierre", "Michel", "Andre", "Philippe", "Rene", "Louis", "Alain", "Jacques", "Bernard",
                     "Marcel", "Daniel", "Roger", "Robert", "Paul", "Claude", "Christian", "Henri", "Georges", "Nicolas",
                     "Francois", "Patrick", "Gerard", "Christophe", "Joseph", "Julien", "Maurice", "Laurent", "Frederic", "Eric",
                     "David", "Stephane", "Pascal", "Sebastien", "Alexandre", "Thierry", "Olivier", "Thomas", "Antoine", "Raymond",
                     "Guy", "Dominique", "Charles", "Didier", "Marc", "Vincent", "Yves", "Guillaume", "Bruno", "Serge",
                     "Maxime", "Marie", "Jeanne", "Francoise", "Monique", "Catherine", "Nathalie", "Isabelle", "Jacqueline", "Anne",
                     "Sylvie", "Martine", "Madeleine", "Nicole", "Suzanne", "Helene", "Christine", "Marguerite", "Denise", "Louise",
                     "Christiane", "Yvonne", "Valerie", "Sophie", "Sandrine", "Stephanie", "Celine", "Veronique", "Chantal", "Marcelle",
                     "Renee", "Simone", "Jeannine", "Julie", "Paulette", "Germaine", "Annie", "Patricia", "Yvette", "Brigitte",
                     "Lucie", "Camille", "Lea", "Odette", "Emilie", "Alice", "Genevieve", "Aurelie", "Laurence", "Michele"
            };

            runner << poids << sp << taille << sp << shoes << sp << vtprec << sp << prepa << sp << dossard << sp << tab[rand()%100] << endl;
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
            string prenom = n[6];
            //
            cout << poids << sp << taille << sp << shoes << sp << vtprec << sp << prepa << sp << dossard << sp << prenom << endl;
            //

            Runner rene(poids, taille, shoes, vtprec, prepa, dossard);
            
            float v = 0;
            int w = 0;
            InfosRunner b(rene, v, v, w, prenom);
            array[count] = b;

            count++;
        }
        runner.close();

        return array;
    }
    else cout << "Impossible d'ouvrir le fichier" << endl;
}