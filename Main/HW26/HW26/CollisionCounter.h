#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class CollisionCounter
{
public:
    CollisionCounter();
    void update(bool collided);
    void draw(sf::RenderWindow* window);
    void incrementCounter() { m_collisionsCounter++; }

private:
    sf::Uint16 m_collisionsCounter = 0;
    sf::Font m_font;
    sf::Text m_text;

    bool m_collidedLastFrame = false;

    sf::Sound m_damageSound;
    sf::SoundBuffer m_buffer;
};
