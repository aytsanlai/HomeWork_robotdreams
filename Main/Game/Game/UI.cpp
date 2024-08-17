#include "UI.h"

UI::UI() : level(1), coins(0) {
    // Load font
    if (!font.loadFromFile("Font/BALOO2-SEMIBOLD.TTF")) {
        
    }

    // Set up level text
    levelText.setFont(font);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(20, 20);

    // Set up coins text
    coinsText.setFont(font);
    coinsText.setCharacterSize(24);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setPosition(20, 60);

    // Set up Bomb button
    bombButton.setFont(font);
    bombButton.setCharacterSize(24);
    bombButton.setFillColor(sf::Color::Red);
    bombButton.setString("Bomb");
    bombButton.setPosition(700, 20);

    // Set up Ice button
    iceButton.setFont(font);
    iceButton.setCharacterSize(24);
    iceButton.setFillColor(sf::Color::Cyan);
    iceButton.setString("Ice");
    iceButton.setPosition(800, 20);
}

void UI::setLevel(int newLevel) {
    level = newLevel;
    levelText.setString("Level: " + std::to_string(level));
}

void UI::setCoins(int newCoins) {
    coins = newCoins;
    coinsText.setString("Coins: " + std::to_string(coins));
}

void UI::draw(sf::RenderWindow& window) {
    window.draw(levelText);
    window.draw(coinsText);
    window.draw(bombButton);
    window.draw(iceButton);
}

bool UI::isButtonClicked(const sf::Vector2i& mousePos, const std::string& button) {
    if (button == "Bomb") {
        return bombButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
    else if (button == "Ice") {
        return iceButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
    return false;
}
