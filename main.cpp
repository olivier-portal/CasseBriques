#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Sleep.hpp>
#include <chrono>
#include <iostream>

int main() {
    std::cout << "[INFO] Demarrage programme...\n";
    std::cout << "[INFO] start\n";
 
    std::cout << "[INFO] opened\n";


    // Petite pause pour te laisser voir les logs avant l'ouverture
    sf::sleep(std::chrono::milliseconds(300));

    sf::RenderWindow window;
    window.create(sf::VideoMode(sf::Vector2u{800u, 600u}), "SFML 3 - Smoke test");

    if (!window.isOpen()) {
        std::cerr << "[ERREUR] La fenetre n'a pas pu s'ouvrir.\n";
        sf::sleep(std::chrono::seconds(3));
        return 1;
    }

    // Rendez-la bien visible au premier plan
    window.setVisible(true);
    window.requestFocus();
    // Optionnel : place-la vers le coin haut-gauche
    // (setPosition prend un Vector2i en SFML 3)
    // window.setPosition(sf::Vector2i{50, 50});

    std::cout << "[INFO] Fenetre ouverte.\n";

    window.setFramerateLimit(60);

    sf::CircleShape ball(60.f);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition(sf::Vector2f{100.f, 100.f});

    while (window.isOpen()) {
        while (auto e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }

    std::cout << "[INFO] Fenetre fermee.\n";
    return 0;
}
