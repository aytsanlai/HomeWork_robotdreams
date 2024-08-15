#include "CollisionCounter.h"
#include "FontManager.h"
#include "SoundManager.h"

CollisionCounter::CollisionCounter()
{
    m_text.setFont(FontManager::getInstance().getDefaultFont());

    m_text.setCharacterSize(48); // in pixels, not points!
    m_text.setFillColor(sf::Color::White);
}

void CollisionCounter::update(bool collided)
{
    if (collided && !m_collidedLastFrame)
    {
        incrementCounter();

        SoundManager::getInstance().playDamage();
    }

    m_collidedLastFrame = collided;

    m_text.setString("Collisions counter: " + std::to_string(m_collisionsCounter));
}

void CollisionCounter::draw(sf::RenderWindow* window)
{
    window->draw(m_text);
}
