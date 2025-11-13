# pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace game {
    class Brick {
    public:
        Brick(sf::Vector2f pos, sf::Vector2f size, const sf::Texture* normalTex, const sf::Texture* crackedTex, int hp) :
        normalTex_{normalTex}, crackedTex_{crackedTex}, hp_(hp), maxHp_(hp) {
            shape_.setPosition(pos);
            shape_.setSize(size);
            shape_.setFillColor(sf::Color::White); // No color
            updateTexture();
        }

        void render(sf::RenderTarget& target) const {
            if (hp_ > 0)
                target.draw(shape_);
        }

        bool isAlive() const noexcept { return hp_ > 0; }

        void hit() noexcept {
            if (hp_ > 0) {
                --hp_;
                updateTexture();
            }
        }

        const sf::RectangleShape& shape() const noexcept { return shape_; }

        private:
        void updateTexture() {
           if (hp_ <= 0) {
            // on pourrait aussi mettre alpha 0
            shape_.setTexture(nullptr);
            shape_.setFillColor(sf::Color::Transparent);
            return;
        }

        if (hp_ >= 2) {
            // full HP / normal sprite
            if (normalTex_) shape_.setTexture(normalTex_);
        } else if (hp_ == 1) {
            // dernier HP / broken sprite
            if (crackedTex_) shape_.setTexture(crackedTex_);
            else if (normalTex_) shape_.setTexture(normalTex_);
        }
        }
        sf::RectangleShape shape_;
        const sf::Texture*  normalTex_{nullptr};
        const sf::Texture*  crackedTex_{nullptr};
        int hp_{0};
        int maxHp_{0};
    };

} // namespace game