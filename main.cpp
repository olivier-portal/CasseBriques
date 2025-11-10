#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Sleep.hpp>
#include <chrono>
#include <iostream>

int main() {
    std::cout << "[INFO] Demarrage programme...\n";
  
    sf::sleep(std::chrono::milliseconds(300));

    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;

    sf::RenderWindow window;
    window.create(sf::VideoMode(sf::Vector2u{screenWidth, screenHeight}), "Casse-brique", sf::Style::Default);

    if (!window.isOpen()) {
        std::cerr << "[ERREUR] La fenetre n'a pas pu s'ouvrir.\n";
        sf::sleep(std::chrono::seconds(3));
        return 1;
    }

    // Visible au premier plan
    window.setVisible(true);
    window.requestFocus();

    std::cout << "[INFO] Fenetre ouverte.\n";

    window.setFramerateLimit(60);

    sf::RectangleShape raquette(sf::Vector2f{100.f, 20.f});
    raquette.setFillColor(sf::Color(255, 165, 0));
    raquette.setPosition(sf::Vector2f{100.f, screenHeight - (10.f + raquette.getSize().y)});

    while (window.isOpen()) {
        while (auto e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            raquette.move({-1.f, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            raquette.move({1.f, 0.f});
        window.clear(sf::Color(57,61,71));
        window.draw(raquette);
        window.display();
    }

    std::cout << "[INFO] Fenetre fermee.\n";
    return 0;

}