#pragma once
#include "GameObjects.h"

class Player : public GameObject
{
public:
    Player();
    void update(float deltaTime) override;

private:
    void handleMovemenent(float deltaTime);
    void handleScale(float deltaTime);
    void handleRotation(float deltaTime);

private:
    float m_speed = 1000.0f;
};