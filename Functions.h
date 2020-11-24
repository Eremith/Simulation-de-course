#pragma once
#include "Class.h"
#include <SFML/Graphics.hpp>

int generatePath(int km); //génère un certain nombre de points3D dans un fichier pour s'approcher de int km
int readPath(int km, sf::ConvexShape* convex, sf::VertexArray* lines); //lis le fichier path.txt pour l'afficher avec sfml
int printPath(sf::ConvexShape c, sf::VertexArray l, InfosRunner* array, int nb, int km);
int generateRunner(int nbrunner);
InfosRunner *readRunner(int nbrunner);