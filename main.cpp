#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Sleep.hpp>
#include <chrono>
#include <iostream>

int main() {
    std::cout << "[INFO] Starting programm...\n";
  
    sf::sleep(std::chrono::milliseconds(300));

    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;

    sf::RenderWindow window;
    window.create(sf::VideoMode(sf::Vector2u{screenWidth, screenHeight}), "Bricks Breaker", sf::Style::Default);

    if (!window.isOpen()) {
        std::cerr << "[ERROR] The window could not open.\n";
        sf::sleep(std::chrono::seconds(3));
        return 1;
    }

    // Show on top and focus
    window.setVisible(true);
    window.requestFocus();

    std::cout << "[INFO] Window open.\n";

    // Set to 60 FPS max
    window.setFramerateLimit(60);

    // Draw paddle & set start position
    sf::RectangleShape paddle(sf::Vector2f{100.f, 20.f});
    paddle.setFillColor(sf::Color(255, 165, 0));
    paddle.setPosition(sf::Vector2f{(screenWidth / 2) - (paddle.getSize().x / 2), screenHeight - (10.f + paddle.getSize().y)});

    // Draw ball & set start position
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(sf::Vector2f{(screenWidth / 2) - ball.getRadius(), paddle.getPosition().y - (10.f + ball.getRadius() * 2)});

    // Put window boundaries
    float leftBoundary = 0.f;
    float rightBoundary = static_cast<float>(screenWidth);
    float rightPaddleBoundary = static_cast<float>(screenWidth) - paddle.getSize().x;

    // Set boundaries for paddle movement
    sf::FloatRect boundyBox = paddle.getGlobalBounds();

    float paddleX = paddle.getPosition().x;


    while (window.isOpen()) {
        while (auto e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            paddle.move({-10.f, 0.f});
            ball.move({-10.f, 0.f});
        }
            
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            paddle.move({10.f, 0.f});
            ball.move({10.f, 0.f});
        }

            if (paddleX < leftBoundary) {
        paddle.setPosition(sf::Vector2f{leftBoundary, paddle.getPosition().y});
            } else if (paddleX > rightPaddleBoundary) {
                paddle.setPosition(sf::Vector2f{rightPaddleBoundary, paddle.getPosition().y});
            }
            
        window.clear(sf::Color(57,61,71));
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    std::cout << "[INFO] window closed.\n";
    return 0;

}