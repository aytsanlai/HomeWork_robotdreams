#pragma once
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	//Add other fonts if needed
	const sf::Font& getDefaultFont() const { return m_defaultFont; }
	sf::Text getDefaultText() const { return m_defaultEmptyText; }

	static FontManager& getInstance() 
	{
		static FontManager instance; 
		return instance; 
	}

private:
	FontManager() 
	{
		m_defaultFont.loadFromFile("arial.ttf"); 
	}
	
	sf::Font m_defaultFont;
	sf::Text m_defaultEmptyText;
};