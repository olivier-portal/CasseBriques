#include "game/Game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <iostream>

namespace game {

// Constructor
Game::Game(unsigned int width, unsigned int height, std::string title)
: width_{width}, height_{height} {
std::cout << "[INFO] Starting program...";
sf::sleep(sf::milliseconds(300));


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
paddle_ = Paddle({100.f, 20.f}, { (width_ / 2.f) - 50.f, height_ - (10.f + 20.f) });
ball_ = Ball(10.f);
ball_.resetOnPaddle(paddle_);


std::cout << "[INFO] Window open.";
}


void Game::handleEvents() {
while (auto e = window_.pollEvent()) {
if (e->is<sf::Event::Closed>())
window_.close();
}
}


void Game::update(float dtSeconds) {
(void)dtSeconds; // frame-based pour rester fidèle à votre version
paddle_.update(dtSeconds, paddleSpeed_, static_cast<float>(width_));
ball_.update(dtSeconds, static_cast<float>(width_), static_cast<float>(height_), paddle_);
}


void Game::render() {
window_.clear(sf::Color(57, 61, 71));
paddle_.render(window_);
ball_.render(window_);
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