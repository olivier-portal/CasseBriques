#include "game/Ball.hpp"
#include "game/Paddle.hpp"
#include "core/Collision.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

namespace game {

Ball::Ball(float radius) {
shape_.setRadius(radius);
shape_.setFillColor(sf::Color::White);
}

// Initial position on paddle before launch
void Ball::resetOnPaddle(const Paddle& paddle) noexcept {
const auto& ps = paddle.shape();
const auto paddlePos = ps.getPosition();
const auto paddleSize = ps.getSize();
const float r = shape_.getRadius();
shape_.setPosition({
paddlePos.x + paddleSize.x / 2.f - r,
paddlePos.y - (r * 2.f)
});
}


// Launch ball
void Ball::launch(sf::Vector2f initialVelocity) noexcept {
velocity_ = initialVelocity;
launched_ = true;
}

// Bounce on bricks
void Ball::bounceY() noexcept {
    velocity_.y = -velocity_.y;
}

void Ball::update(float /*dtSeconds*/, float screenWidth, float screenHeight, const Paddle& paddle) noexcept {
// Launched if spaceBar is pressed
if (!launched_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
launch({0.f, -6.f});
}

if (!launched_) {
resetOnPaddle(paddle);
} else {
shape_.move(velocity_);
}

auto pos = shape_.getPosition();
const float diam = shape_.getRadius() * 2.f;


// Ball bouncing on walls


// left & right Wall
if (pos.x <= 0.f) { velocity_.x = std::abs(velocity_.x); pos.x = 0.f; }
if (pos.x + diam >= screenWidth) { velocity_.x = -std::abs(velocity_.x); pos.x = screenWidth - diam; }


// top wall
if (pos.y <= 0.f) { velocity_.y = std::abs(velocity_.y); pos.y = 0.f; }


shape_.setPosition(pos);


// Bounce on paddle
if (velocity_.y > 0.f && core::aabbIntersects(shape_.getGlobalBounds(), paddle.shape().getGlobalBounds())) {
    // Reverse speed on Y axis
    velocity_.y = -std::abs(velocity_.y);
    shape_.setPosition({ shape_.getPosition().x, paddle.shape().getPosition().y - diam - 0.1f });


    // Variation of the hit angle based on where it hits the paddle
    const float paddleCenter = paddle.shape().getPosition().x + paddle.shape().getSize().x / 2.f;
    const float hitX = shape_.getPosition().x + shape_.getRadius();
    const float offset = (hitX - paddleCenter) / (paddle.shape().getSize().x / 2.f); // [-1, 1]
    velocity_.x = 7.f * offset;
}

// Ball resets if below screen
if (shape_.getPosition().y > screenHeight) {
launched_ = false;
velocity_ = {0.f, 0.f};
resetOnPaddle(paddle);
}
}


void Ball::render(sf::RenderTarget& target) const { target.draw(shape_); }


} // namespace game