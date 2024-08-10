#pragma once
#include "GameObjects.h"
#include "Pathfinder.h"
#include "Map.h"

class Player : public GameObject
{
public:
    Player();
    void update(float deltaTime) override;

private:
    void handleMovemenent(float deltaTime);
    void handleScale(float deltaTime);
    void handleRotation(float deltaTime);

    Pathfinder pathfinder_;
    std::vector<sf::Vector2f> path_; 

    void updatePath(sf::Vector2f target);
    void moveTowards(sf::Vector2f target, float deltaTime);

private:
    float m_speed = 1000.0f;
};

