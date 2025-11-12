#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace core {

[[nodiscard]] inline bool aabbIntersects(const sf::FloatRect& a, const sf::FloatRect& b) noexcept {
#if defined(SFML_VERSION_MAJOR) && (SFML_VERSION_MAJOR >= 3)
    // SFML 3.x : FloatRect -> position/size
    return (a.position.x < b.position.x + b.size.x) &&
           (a.position.x + a.size.x > b.position.x) &&
           (a.position.y < b.position.y + b.size.y) &&
           (a.position.y + a.size.y > b.position.y);
#else
    // SFML 2.x : FloatRect -> left/top/width/height
    return (a.left < b.left + b.width) &&
           (a.left + a.width > b.left) &&
           (a.top < b.top + b.height) &&
           (a.top + a.height > b.top);
#endif
}

} // namespace core
