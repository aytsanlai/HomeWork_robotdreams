#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

class ItemDatabase {
public:
    std::vector<std::string> loadItems(const std::string& filename) {
        std::vector<std::string> items;
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }

        std::string line;
        while (std::getline(file, line)) {
            items.push_back(line);
        }

        file.close();
        return items;
    }
};
