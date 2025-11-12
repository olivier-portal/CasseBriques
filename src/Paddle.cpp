#include "game/Paddle.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace game {

// Get paddle position
Paddle::Paddle(sf::Vector2f size, sf::Vector2f pos) {
shape_.setSize(size);
shape_.setFillColor(sf::Color(255, 165, 0));
shape_.setPosition(pos);
}


// Paddle movement
void Paddle::update(float /*dtSeconds*/, float speed, float screenWidth) {
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) shape_.move({-speed, 0.f});
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) shape_.move({+speed, 0.f});


// Keep paddle inside screen bounds
auto pos = shape_.getPosition();
const auto w = shape_.getSize().x;
if (pos.x < 0.f) pos.x = 0.f;
if (pos.x + w > screenWidth) pos.x = screenWidth - w;
shape_.setPosition(pos);
}

void Paddle::render(sf::RenderTarget& target) const { target.draw(shape_); }

} // namespace game