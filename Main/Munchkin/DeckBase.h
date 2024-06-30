#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class DeckBase {
protected:
    std::vector<std::string> items;

    template<typename T>
    T generateUniqueItem(const std::vector<T>& allItems, std::vector<T>& usedItems) {
        std::vector<T> availableItems;
        std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(availableItems), [&usedItems](const T& item) {
            return std::find(usedItems.begin(), usedItems.end(), item) == usedItems.end();
            });

        if (availableItems.empty()) {
            throw std::runtime_error("No unique items available");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, availableItems.size() - 1);

        T selectedItem = availableItems[dis(gen)];
        usedItems.push_back(selectedItem);
        return selectedItem;
    }
};
