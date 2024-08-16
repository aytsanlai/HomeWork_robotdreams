#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	void playDamage() { m_collisionSound.play(); }
	void playJump() { m_jumpSound.play(); }
	void playGameStart() { m_startGameSound.play(); }

	static SoundManager& getInstance() 
	{
		static SoundManager instance; 
		return instance; 
	}

private:
	SoundManager()
	{
		m_damageBuffer.loadFromFile("damage.wav");
		m_jumpBuffer.loadFromFile("jump.wav");
		m_startGameBuffer.loadFromFile("game_start.wav");

		m_collisionSound.setBuffer(m_damageBuffer);
		m_jumpSound.setBuffer(m_jumpBuffer);
		m_startGameSound.setBuffer(m_startGameBuffer);
	}

	sf::Sound m_jumpSound;
	sf::Sound m_collisionSound;
	sf::Sound m_startGameSound;

	sf::SoundBuffer m_jumpBuffer;
	sf::SoundBuffer m_damageBuffer;
	sf::SoundBuffer m_startGameBuffer;
};