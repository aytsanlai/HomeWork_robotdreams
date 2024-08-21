#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"

class TaskManager {
public:
    TaskManager();

    void setTask(TileType type, int count, const std::string& textureFile);
    bool checkCompletion(TileType type, int count);
    void draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position);

    bool isTaskCompleted() const { return completed; }
    TileType getTaskType() const { return taskType; }

private:
    TileType taskType;
    int taskCount;
    int currentCount;
    bool completed;

    sf::Texture taskTexture;
    sf::Sprite taskSprite;
    sf::Text taskText;
};
