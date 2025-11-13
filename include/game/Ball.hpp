#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace game {

class Paddle; // fwd decl

class Ball {
public:
explicit Ball(float radius = 10.f);

void resetOnPaddle(const Paddle& paddle) noexcept;
void launch(sf::Vector2f initialVelocity) noexcept;
void update(float dtSeconds, float screenWidth, float screenHeight, const Paddle& paddle) noexcept;
void render(sf::RenderTarget& target) const;
void bounceY() noexcept;

[[nodiscard]] const sf::CircleShape& shape() const noexcept { return shape_; }
[[nodiscard]] sf::CircleShape& shape() noexcept { return shape_; }

private:
sf::CircleShape shape_;
sf::Vector2f velocity_{0.f, 0.f};
bool launched_{false};
};

} // namespace game