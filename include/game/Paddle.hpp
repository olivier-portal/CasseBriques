#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace game {

class Paddle {
public:
explicit Paddle(sf::Vector2f size = {100.f, 20.f}, sf::Vector2f pos = {0.f, 0.f});

void update(float dtSeconds, float speed, float screenWidth);
void render(sf::RenderTarget& target) const;

[[nodiscard]] const sf::RectangleShape& shape() const noexcept { return shape_; }
[[nodiscard]] sf::RectangleShape& shape() noexcept { return shape_; }

private:
sf::RectangleShape shape_;
};

} // namespace game