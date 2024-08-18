#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

struct Particle {
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Starburst Effect");

    // Load the texture for the particles
    sf::Texture texture;
    if (!texture.loadFromFile("images/NewNodes/Star.png")) { 
        std::cerr << "Error: Could not load texture!" << std::endl;
        return -1;
    }

    std::vector<Particle> particles;
    sf::Clock clock;

    const int maxParticles = 10; // Max particles like Unity
    const float startLifetime = 0.4f; // Start lifetime of particles
    const float startSpeed = 2.0f; // Speed of particles
    const float startSize = 0.175f * 100.0f; // Size
    const int emissionCount = 10; // Particles emitted
    const float emissionRadius = 0.24f * 100.0f; // Adjusted radius for visibility

    bool burstTriggered = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float elapsedTime = clock.restart().asSeconds();

        if (!burstTriggered) {
            // Emit particles
            for (int i = 0; i < emissionCount; i++) {
                Particle particle;
                particle.sprite.setTexture(texture);
                particle.sprite.setScale(startSize / texture.getSize().x, startSize / texture.getSize().y);
                particle.sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
                particle.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

                // Random direction within a circle
                float angle = static_cast<float>(rand()) / RAND_MAX * 2 * M_PI;
                particle.velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * startSpeed;
                particle.lifetime = startLifetime;

                particles.push_back(particle);
            }
            burstTriggered = true;
        }

        // Update particles
        for (auto it = particles.begin(); it != particles.end(); ) {
            it->lifetime -= elapsedTime;
            if (it->lifetime <= 0) {
                it = particles.erase(it);
            }
            else {
                it->sprite.move(it->velocity);
                std::cout << "Particle position: " << it->sprite.getPosition().x << ", " << it->sprite.getPosition().y << std::endl;

                // Set alpha based on lifetime (fade out effect)
                it->sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * it->lifetime / startLifetime)));
                ++it;
            }
        }

        window.clear();

        // Draw particles
        for (const auto& particle : particles) {
            window.draw(particle.sprite);
        }

        window.display();
    }

    return 0;
}
