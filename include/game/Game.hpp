#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include "game/Paddle.hpp"
#include "game/Ball.hpp"
#include "game/BrickGrid.hpp"

namespace game {

class Game {
public:
Game(unsigned int width, unsigned int height, std::string title);
int run();

private:
void handleEvents();
void update(float dtSeconds);
void render();

sf::RenderWindow window_;
unsigned int width_{};
unsigned int height_{};

Paddle paddle_;
Ball ball_;
BrickGrid bricks_;

// Config
float paddleSpeed_ { 10.f };
};

} // namespace game