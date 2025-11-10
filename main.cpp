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

    unsigned int screenWidth = 900;
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
    paddle.setPosition(sf::Vector2f{(screenWidth / 2.f) - (paddle.getSize().x / 2), screenHeight - (10.f + paddle.getSize().y)});

    // Draw ball
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);

    // Make ball follow paddle before launch
        auto ballBeforeLaunch = [&]() {
            ball.setPosition(sf::Vector2f{paddle.getPosition().x + paddle.getSize().x / 2.f - ball.getRadius(),
                                      paddle.getPosition().y - (ball.getRadius() * 2.f)});
        };

    // Ball status
    bool isLaunched = false;
    sf::Vector2f ballVelocity = {0.f, 0.f};

    // Movement const
    const float paddleSpeed = 10.f;
    const float leftBoundary = 0.f;
    const float rightBoundary = static_cast<float>(screenWidth);

    while (window.isOpen()) {
        while (auto e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) window.close();
        }

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            paddle.move({-paddleSpeed, 0.f});
            ball.move({-paddleSpeed, 0.f});
        }
            
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            paddle.move({paddleSpeed, 0.f});
            ball.move({paddleSpeed, 0.f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            ball.move({0.f, paddleSpeed});
        }

        // Get paddle position
        sf::Vector2f pos = paddle.getPosition();

        // Boundary check
        if (pos.x < leftBoundary) { 
            pos.x = leftBoundary;
        }
        else if (pos.x + paddle.getSize().x > rightBoundary) {
            pos.x = rightBoundary - paddle.getSize().x;
        }

        paddle.setPosition(pos);

        // Launch ball
        if (!isLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            isLaunched = true;
            ballVelocity = sf::Vector2f{4.f, -6.f};
        }

        // Keep ball on paddle before launch
        if (!isLaunched) {
            ballBeforeLaunch();
        } else {
            ball.move(ballVelocity);
        }
            
        window.clear(sf::Color(57,61,71));
        window.draw(paddle);
        window.draw(ball);
        window.display();
    }

    std::cout << "[INFO] window closed.\n";
    return 0;

}