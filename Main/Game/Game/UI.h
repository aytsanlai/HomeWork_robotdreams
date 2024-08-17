#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UI {
public:
    UI();
    void setLevel(int level);
    void setCoins(int coins);
    void draw(sf::RenderWindow& window);
    bool isButtonClicked(const sf::Vector2i& mousePos, const std::string& button);

private:
    int level;
    int coins;
    sf::Font font;
    sf::Text levelText;
    sf::Text coinsText;
    sf::Text bombButton;
    sf::Text iceButton;
};
