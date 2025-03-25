#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

// #include <memory>
#include <vector>
#include <string>
// #include "Tile.hpp"
// #include "Util/Renderer.hpp"

class MapLoader {
public:
    MapLoader();
    // MapLoader(Util::Renderer& m_Root);
    bool loadMap(const std::string& fileName);

    // void createTileObjects();

    void printMap() const;

    [[nodiscard]] int getWidth() const { return width; }

    [[nodiscard]] int getHeight() const { return height; }

    std::vector<std::vector<int>> GetMap() { return tiles; }

private:
    int width;
    int height;
    std::vector<std::vector<int>> tiles;
    // std::vector<std::vector<Tile*>> tileObjects;
    // std::shared_ptr<Util::Renderer> Root;
};

#endif // MAPLOADER_HPP
