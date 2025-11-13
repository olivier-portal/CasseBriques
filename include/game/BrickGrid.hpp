# pragma once
#include "game/Brick.hpp"
#include <vector>

namespace game {

class BrickGrid {
public:
    BrickGrid(unsigned rows, unsigned cols, sf::Vector2f size, float padding, sf::Vector2f start) {
        
        bricks_.reserve(rows * cols);

        for (unsigned r = 0; r < rows; ++r) {
            for (unsigned c = 0; c < cols; ++c) {
                int hp = 1;
                if (r == 0) hp = 3;
                else if (r == 1) hp = 2;
                else if (r == 3) hp = 2;
                else if (r == 4) hp = 3;
                else hp = 1;

                sf::Vector2f pos {
                    start.x + c * (size.x + padding),
                    start.y + r * (size.y + padding)
                };

                bricks_.emplace_back(pos, size, hp);
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