#include "MapLoader.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

MapLoader::MapLoader() : width(0), height(0) {}

bool MapLoader::loadMap(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Read first line: "{"
    std::getline(file, line); // Read second line: "    \"width\": 5,"
    width = std::stoi(line.substr(line.find(":") + 1));

    std::getline(file, line); // Read third line: "    \"height\": 5,"
    height = std::stoi(line.substr(line.find(":") + 1));

    std::getline(file, line); // Read fourth line: "    \"tiles\": ["
    
    // Read the tiles matrix (we assume the tiles are in the correct format)
    tiles.resize(height);
    for (int i = 0; i < height; ++i) {
        std::getline(file, line);
        line = line.substr(1, line.size() - 2);
        // LOG_DEBUG(line);
        std::istringstream stream(line);
        std::string temp;
        while (std::getline(stream, temp, ',')){
            tiles[i].push_back(std::stoi(temp));
        }
    }

    return true;
}

void MapLoader::printMap() const {
    std::cout << "Map Dimensions: " << width << "x" << height << std::endl;
    for (const auto& row : tiles) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}
