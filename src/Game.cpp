#include "game/Game.hpp"
#include "game/BrickGrid.hpp"
#include "core/Collision.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>

namespace game {

// Constructor
Game::Game(unsigned int width, unsigned int height, std::string title)
: width_{width}
, height_{height}
, paddle_({100.f, 20.f}, { (width / 2.f) - 50.f, height - (10.f + 20.f) })
, ball_(10.f)
, bricks_(0, 0, {0.f, 0.f}, 0.f, {0.f, 0.f},
          texBlue_, texBlueBroken_,
          texGreen_, texGreenBroken_,
          texOrange_, texOrangeBroken_,
          texPurple_, texPurpleBroken_,
          texRed_, texRedBroken_) {
std::cout << "[INFO] Starting program...";
sf::sleep(sf::milliseconds(300));

// Loading textures
    if (!texBlue_.loadFromFile("assets/BlueTile.png") ||
        !texBlueBroken_.loadFromFile("assets/BreakedBlueTile.png") ||
        !texGreen_.loadFromFile("assets/GreenTile.png") ||
        !texGreenBroken_.loadFromFile("assets/BreakedGreenTile.png") ||
        !texOrange_.loadFromFile("assets/OrangeTile.png") ||
        !texOrangeBroken_.loadFromFile("assets/BreakedOrangeTile.png") ||
        !texPurple_.loadFromFile("assets/PurpleTile.png") ||
        !texPurpleBroken_.loadFromFile("assets/BreakedPurpleTile.png") ||
        !texRed_.loadFromFile("assets/RedTile.png") ||
        !texRedBroken_.loadFromFile("assets/BreakedRedTile.png")) {
        std::cerr << "[ERROR] Could not load brick textures\n";
    }


// Create window
window_.create(sf::VideoMode(sf::Vector2u{width_, height_}), title, sf::Style::Default);
if (!window_.isOpen()) {
std::cerr << "[ERROR] The window could not open.";
sf::sleep(sf::seconds(3));
return;
}

window_.setVisible(true);
window_.requestFocus();
window_.setFramerateLimit(60);

// Position of ball on paddle at start

ball_.resetOnPaddle(paddle_);

// Set brick size
    sf::Vector2f brickSize{96.f, 32.f};

// Set BrickGrid
bricks_ = BrickGrid(
        5, 8,                   // 5 rows, 8 colons
        brickSize,               // Brick size
        5.f,                     // padding
        {35.f, 50.f},            // start position 
        texBlue_, texBlueBroken_,
        texGreen_, texGreenBroken_,
        texOrange_, texOrangeBroken_,
        texPurple_, texPurpleBroken_,
        texRed_, texRedBroken_
    );

std::cout << "[INFO] Window open.";
}

void Game::handleEvents() {
    while (auto event = window_.pollEvent()) {
        // event est un std::optional<sf::Event>
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
    }
}

void Game::update(float dtSeconds) {

    (void)dtSeconds; // frame-based

    paddle_.update(dtSeconds, paddleSpeed_, static_cast<float>(width_));
    ball_.update(dtSeconds, static_cast<float>(width_), static_cast<float>(height_), paddle_);

    // Bricks collision with ball
    for (auto& brick : bricks_.bricks()) {
        if (brick.isAlive() && core::aabbIntersects(ball_.shape().getGlobalBounds(), brick.shape().getGlobalBounds())) {
            brick.hit();
            ball_.bounceY();
            break;
        }
    }

    // Victory check
    bool allDestroyed = true;

    for (const auto& brick : bricks_.bricks()) {
        if (brick.isAlive()) {
            allDestroyed = false;
            break;
        }
    }

    if (allDestroyed) {
        std::cout << "Victory !!!!";
        window_.close();
    }

}


void Game::render() {
window_.clear(sf::Color(57, 61, 71));
paddle_.render(window_);
ball_.render(window_);
bricks_.render(window_);
window_.display();
}


int Game::run() {
if (!window_.isOpen()) return 1;


sf::Clock clock;
while (window_.isOpen()) {
const float dt = clock.restart().asSeconds();
handleEvents();
update(dt);
render();
}

std::cout << "[INFO] Window closed.";
return 0;
}


} // namespace game