#include "GameObject.h"
#include "Component.h"
#include "Map.h"
#include "GameWorld.h"

GameObject::GameObject(const char* textureFileName) : m_texture() {
    if (!m_texture.loadFromFile(textureFileName)) {
        // Handle error
    }
    m_sprite.setTexture(m_texture);
}

GameObject::~GameObject() {
    for (Component* component : m_components) {
        delete component;
    }
}

void GameObject::update(float deltaTime) {
    for (Component* component : m_components) {
        component->update(deltaTime);
    }
}

void GameObject::draw(sf::RenderWindow* window) {
    window->draw(m_sprite);

    for (Component* component : m_components) {
        component->draw(window);
    }
}

void GameObject::setPosition(const sf::Vector2f& position) {
    m_sprite.setPosition(position);
}

sf::Vector2f GameObject::getPosition() const {
    return m_sprite.getPosition();
}

void GameObject::updatePosition(const sf::Vector2f& deltaPosition) {
    sf::Vector2f position = getPosition();
    if (!Map::GetInstance().isTileBlocked({ position.x + deltaPosition.x, position.y })) {
        position.x += deltaPosition.x;
    }

    if (!Map::GetInstance().isTileBlocked({ position.x, position.y + deltaPosition.y })) {
        position.y += deltaPosition.y;
    }

    setPosition(position);
}

sf::Vector2f GameObject::getSize() const {
    return m_sprite.getLocalBounds().getSize();
}

sf::Sprite* GameObject::getSprite() {
    return &m_sprite;
}

void GameObject::addComponent(Component* component) {
    m_components.push_back(component);
}

Component* GameObject::getComponent(const std::string& name) {
    for (Component* component : m_components) {
        if (component->getName() == name) {
            return component;
        }
    }
    return nullptr;
}

VisibilityPriority GameObject::getVisibilityPriority() const {
    return m_visibilityPriority;
}

void GameObject::setVisibilityPriority(VisibilityPriority priority) {
    m_visibilityPriority = priority;
}