#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
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

// bricks textures
    sf::Texture texBlue_;
    sf::Texture texBlueBroken_;
    sf::Texture texGreen_;
    sf::Texture texGreenBroken_;
    sf::Texture texOrange_;
    sf::Texture texOrangeBroken_;
    sf::Texture texPurple_;
    sf::Texture texPurpleBroken_;
    sf::Texture texRed_;
    sf::Texture texRedBroken_;

// Show victory
    sf::Font font_;
    sf::Text victoryText_;
    bool victory_{false};

// Set paddle speed
    float paddleSpeed_ { 10.f };
    };

} // namespace game