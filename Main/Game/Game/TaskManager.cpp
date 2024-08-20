#include "TaskManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

TaskManager::TaskManager() : taskType(TileType::Red), taskCount(3), currentCount(0), completed(false) {
    if (!taskTexture.loadFromFile("images/NewNodes/Stage3/FrogP.png")) {
        std::cerr << "Failed to load task texture" << std::endl;
    }
    taskSprite.setTexture(taskTexture);
    taskSprite.setScale(0.25f, 0.25f); // Sprite scale
    taskText.setString("Task: 0/3");
}

void TaskManager::setTask(TileType type, int count, const std::string& textureFile) {
    taskType = type;
    taskCount = count;
    currentCount = 0;
    completed = false;
    if (!taskTexture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load task texture" << std::endl;
    }
    taskSprite.setTexture(taskTexture);
    taskSprite.setScale(0.25f, 0.25f); // Sprite scale
    taskText.setString("Task: 0/" + std::to_string(taskCount));
}

bool TaskManager::checkCompletion(TileType type, int count) {
    if (type == taskType) {
        currentCount += count;
        taskText.setString("Task: " + std::to_string(currentCount) + "/" + std::to_string(taskCount));
        if (currentCount >= taskCount) {
            completed = true;
            return true;
        }
    }
    return false;
}

void TaskManager::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f& position) {
    taskText.setFont(font);
    taskText.setFillColor(sf::Color(131, 83, 83)); // Brown color
    taskText.setPosition(position);
    taskText.setCharacterSize(50);
    taskSprite.setPosition(position.x + 25, position.y + 70); // Adjust position as needed
    window.draw(taskText);
    window.draw(taskSprite);
}
