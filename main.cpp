#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point3D.h"
#include "Runner.h"

int main() {

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

    return 0;
}