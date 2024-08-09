#include "Player.h"
#include "Map.h"


Player::Player() : GameObject("MINECRAFT_SPRITE.png")
{
	//Make origin at the center of the sprite rectangle
	m_sprite.setOrigin(m_sprite.getGlobalBounds().getSize().x / 2,
		m_sprite.getGlobalBounds().getSize().y / 2);

	setPosition(Map::GetInstance().getRandomValidPosition());
	//m_components.push_back(new PlayerJumpComponent(this));
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);

	//#TODO, Bohdan: Each can be its own component
	handleMovemenent(deltaTime);
	handleRotation(deltaTime);
	handleScale(deltaTime);
}

void Player::handleMovemenent(float deltaTime)
{
	const float MoveDelta = m_speed * deltaTime;

	float deltaX = 0;
	float deltaY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		deltaX += MoveDelta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		deltaX -= MoveDelta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		deltaY -= MoveDelta;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		deltaY += MoveDelta;
	}

	updatePosition({ deltaX, deltaY });
}

void Player::handleScale(float deltaTime)
{
	constexpr float ScaleSpeed = 0.25f;
	sf::Vector2f scale = m_sprite.getScale();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		scale.x *= -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
	}
	m_sprite.setScale(scale);
}

void Player::handleRotation(float deltaTime)
{
	const float rotationDelta = 100.0f * deltaTime;	//== 100 degrees per second
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_sprite.rotate(rotationDelta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_sprite.rotate(-rotationDelta);
	}
}
