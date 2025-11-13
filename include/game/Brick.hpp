# pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace game {
    class Brick {
    public:
        Brick(sf::Vector2f pos, sf::Vector2f size, int hp) : hp_(hp), maxHp_(hp) {
            shape_.setPosition(pos);
            shape_.setSize(size);
            updateColor();
        }

        void render(sf::RenderTarget& target) const {
            if (hp_ > 0)
                target.draw(shape_);
        }

        bool isAlive() const noexcept { return hp_ > 0; }

        void hit() noexcept {
            if (hp_ > 0) {
                hp_--;
                updateColor();
            }
        }

        const sf::RectangleShape& shape() const noexcept { return shape_; }

        private:
        void updateColor() {
            switch (hp_) {
                case 3: shape_.setFillColor(sf::Color(150, 150, 150)); break; // gray
                case 2: shape_.setFillColor(sf::Color(255, 60, 60)); break;   // red
                case 1: shape_.setFillColor(sf::Color(255, 200, 0)); break;   // Yellow
                default: shape_.setFillColor(sf::Color::Transparent); break;  // invisible
            }
        }
        sf::RectangleShape shape_;
        int hp_{0};
        int maxHp_{0};
    };

} // namespace game