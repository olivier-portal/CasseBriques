# pragma once
#include "game/Brick.hpp"
#include <vector>

namespace game {

class BrickGrid {
public:
    BrickGrid(unsigned rows,
            unsigned cols, 
            sf::Vector2f size, 
            float padding, 
            sf::Vector2f start,
            const sf::Texture& blue,
            const sf::Texture& blueBroken,
            const sf::Texture& green,
            const sf::Texture& greenBroken,
            const sf::Texture& orange,
            const sf::Texture& orangeBroken,
            const sf::Texture& purple,
            const sf::Texture& purpleBroken,
            const sf::Texture& red,
            const sf::Texture& redBroken) {
        
        bricks_.reserve(rows * cols);

        for (unsigned r = 0; r < rows; ++r) {
            for (unsigned c = 0; c < cols; ++c) {

                int hp = 2;

                const sf::Texture* normal = nullptr;
                const sf::Texture* cracked = nullptr;

                switch (r) {
                    case 0: normal = &blue;   cracked = &blueBroken;   break;
                    case 1: normal = &green;  cracked = &greenBroken;  break;
                    case 2: normal = &orange; cracked = &orangeBroken; break;
                    case 3: normal = &purple; cracked = &purpleBroken; break;
                    default: normal = &red;   cracked = &redBroken;    break;
                }

                sf::Vector2f pos {
                    start.x + c * (size.x + padding),
                    start.y + r * (size.y + padding)
                };

                bricks_.emplace_back(pos, size, normal, cracked, hp);
            }
        }
    }

    std::vector<Brick>& bricks() noexcept { return bricks_; }
    const std::vector<Brick>& bricks() const noexcept { return bricks_; }

    void render(sf::RenderTarget& target) const {
        for (const auto& b : bricks_) {
            b.render(target);
        }
    }

private:
    std::vector<Brick> bricks_;

};
} // namespace game