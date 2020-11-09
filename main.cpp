#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(500, 500), "Simulation");
    sf::CircleShape shape(50.f);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}