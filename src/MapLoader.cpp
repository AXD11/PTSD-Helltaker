#include "MapLoader.hpp"
#include "Devil.hpp"
#include "Hero.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
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

    std::getline(file, line); // Read third line: "    \"step\": 5,"
    step = std::stoi(line.substr(line.find(":") + 1));

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

void MapLoader::PrintMap() const {
    std::cout << "Map Dimensions: " << width << "x" << height << std::endl;
    for (const auto& row : tiles) {
        for (int tile : row) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }
}

void MapLoader::SetMap(const glm::vec2& init_position, std::vector<std::shared_ptr<Tile>>& tilePtr, std::vector<std::shared_ptr<Enemy>>& enemyPtr, Util::Renderer& m_Root, std::shared_ptr<Hero>& m_Hero, std::shared_ptr<Devil>& m_Devil) {
    int tmpInt1 = 0, tmpInt2 = 0;
    for (const auto& row : tiles) {
        // LOG_DEBUG("Loading Map...");
        for (int tile : row) {
            // LOG_DEBUG(tile);
            // std::cout << "tmpInt1:" << tmpInt1 << ", tmpInt2:" << tmpInt2 << std::endl;
            switch (tile) {
                case 9:
                    // LOG_DEBUG("Case 0");
                    tilePtr[tmpInt1 + tmpInt2 * width] = std::make_shared<Wall>("Air");
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetPosition({init_position.x + 100 * tmpInt1,init_position.y - 100 * tmpInt2});
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetVisible(true);
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetZIndex(5);
                    m_Root.AddChild(tilePtr[tmpInt1 + tmpInt2 * width]);
                    break;
                case 1:
                    // LOG_DEBUG("Case 0");
                    tilePtr[tmpInt1 + tmpInt2 * width] = std::make_shared<Wall>("Wall2");
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetPosition({init_position.x + 100 * tmpInt1,init_position.y - 100 * tmpInt2});
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetVisible(true);
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetZIndex(5);
                    m_Root.AddChild(tilePtr[tmpInt1 + tmpInt2 * width]);
                    break;
                case 2:
                    // LOG_DEBUG("Case 1");
                    tilePtr[tmpInt1 + tmpInt2 * width] = std::make_shared<Box>();
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetVisible(true);
                    tilePtr[tmpInt1 + tmpInt2 * width]->SetZIndex(1);
                    m_Root.AddChild(tilePtr[tmpInt1 + tmpInt2 * width]);
                    break;
                case 3:
                    m_Hero->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
                    m_Hero->SetCenter();
                    m_Hero->SetLevelStep(step);
                    break;
                case 4:
                    // LOG_DEBUG("Case 4");
                    enemyPtr[tmpInt1 + tmpInt2 * width] = std::make_shared<Enemy>();
                    enemyPtr[tmpInt1 + tmpInt2 * width]->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
                    enemyPtr[tmpInt1 + tmpInt2 * width]->SetVisible(true);
                    enemyPtr[tmpInt1 + tmpInt2 * width]->SetZIndex(4);
                    m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * width]);
                    m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * width]->GetStandbyAnimation());
                    m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * width]->GetBeKickedAnimation());
                    // LOG_DEBUG("index");
                    // LOG_DEBUG(tmpInt1 + tmpInt2 * m_MapLoader.getWidth());
                    // LOG_DEBUG("````");
                    break;
                case 5:
                    m_Devil = std::make_shared<Devil>("Monica");
                    m_Devil->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
                    m_Devil->SetVisible(true);
                    m_Devil->SetZIndex(4);
                    m_Root.AddChild(m_Devil);
                    m_Root.AddChild(m_Devil->GetStandbyAnimation());
                    break;
                default:
                    // LOG_DEBUG("Case default");
                    break;
            }
            tmpInt1++;
        }
        // break;
        // LOG_DEBUG("-----------------");
        tmpInt2++;
        tmpInt1 = 0;
    }
}


void MapLoader::ClearMap(std::vector<std::shared_ptr<Tile>>& tilePtr, std::vector<std::shared_ptr<Enemy>>& enemyPtr, Util::Renderer& m_Root, std::shared_ptr<Devil>& m_Devil) {
    if (m_Devil != nullptr) {
        m_Root.RemoveChild(m_Devil);
        m_Root.RemoveChild(m_Devil->GetStandbyAnimation());
        // m_Devil.reset();
    }

    for (auto& tile : tilePtr) {
        if (tile != nullptr) {
            m_Root.RemoveChild(tile);
            // tile.reset();
        }
    }

    for (auto& enemy : enemyPtr) {
        if (enemy != nullptr) {
            m_Root.RemoveChild(enemy);
            m_Root.RemoveChild(enemy->GetStandbyAnimation());
            m_Root.RemoveChild(enemy->GetBeKickedAnimation());
            // enemy.reset();
        }
    }
}