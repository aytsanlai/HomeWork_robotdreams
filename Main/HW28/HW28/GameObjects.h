#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "VisibilityPriority.h"

class GameObject {
public:
    GameObject(const char* textureFileName);
    virtual ~GameObject();

    virtual void PostInit() {}
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow* window);

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void updatePosition(const sf::Vector2f& deltaPosition);

    sf::Vector2f getSize() const;
    sf::Sprite* getSprite();

    void addComponent(Component* component);
    Component* getComponent(const std::string& name);

    VisibilityPriority getVisibilityPriority() const;
    void setVisibilityPriority(VisibilityPriority priority);

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    std::vector<Component*> m_components;
    VisibilityPriority m_visibilityPriority;
};