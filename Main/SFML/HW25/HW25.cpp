#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
    Player(const sf::Texture& texture) : speed(200.0f) {
        sprite.setTexture(texture);
        sprite.setPosition(100.0f, 100.0f);
        sf::FloatRect bounds = sprite.getGlobalBounds();
        std::cout << "Sprite dimensions: " << bounds.width << "x" << bounds.height << std::endl;
    }

    void handleInput(float deltaTime) {
        sf::Vector2f direction(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction.y -= speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction.y += speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction.x -= speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction.x += speed * deltaTime;
        sprite.move(direction);
    }

    void update(const sf::RenderWindow& window) {
        checkBoundaries(window);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void checkBoundaries(const sf::RenderWindow& window) {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        if (bounds.left < 0) sprite.setPosition(0, bounds.top);
        if (bounds.top < 0) sprite.setPosition(bounds.left, 0);
        if (bounds.left + bounds.width > window.getSize().x) sprite.setPosition(window.getSize().x - bounds.width, bounds.top);
        if (bounds.top + bounds.height > window.getSize().y) sprite.setPosition(bounds.left, window.getSize().y - bounds.height);
    }

private:
    sf::Sprite sprite;
    float speed;
};

void handleSystemEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test Window");

    sf::Texture texture;
    if (!texture.loadFromFile("t.png")) {
        std::cerr << "Failed to load texture from file 't.png'" << std::endl;
        return -1;
    }
    else {
        std::cout << "Texture loaded successfully." << std::endl;
        std::cout << "Texture dimensions: " << texture.getSize().x << "x" << texture.getSize().y << std::endl;
    }

    Player player(texture);

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleSystemEvents(window);

        player.handleInput(deltaTime);
        player.update(window);

        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}
