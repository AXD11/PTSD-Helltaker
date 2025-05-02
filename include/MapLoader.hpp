#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

// #include <memory>
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Spike.hpp"
#include "Enemy.hpp"
#include "Floor.hpp"
#include "Devil.hpp"
#include "Hero.hpp"
#include "Util/Renderer.hpp"
// #include "Util/Renderer.hpp"

class MapLoader {
public:
    MapLoader();
    // MapLoader(Util::Renderer& m_Root);
    bool loadMap(const std::string& fileName);

    // void createTileObjects();

    void PrintMap() const;

    void SetMap(
        const glm::vec2& init_position,
        std::vector<std::shared_ptr<Floor>>& floorPtr,
        std::vector<std::shared_ptr<Tile>>& tilePtr,
        std::vector<std::shared_ptr<Enemy>>& enemyPtr,
        Util::Renderer& m_Root,
        std::shared_ptr<Hero>& m_Hero,
        std::shared_ptr<Devil>& m_Devil
    );

    void ClearMap(
        std::vector<std::shared_ptr<Floor>>& floorPtr,
        std::vector<std::shared_ptr<Tile>>& tilePtr,
        std::vector<std::shared_ptr<Enemy>>& enemyPtr,
        Util::Renderer& m_Root,
        std::shared_ptr<Devil>& m_Devil
    );

    std::vector<std::vector<int>> GetMap() { return tiles; }
    
    [[nodiscard]] int getWidth() const { return width; }

    [[nodiscard]] int getHeight() const { return height; }

    [[nodiscard]] int getStep() const { return step; }

private:
    int width;
    int height;
    int step;
    std::vector<std::vector<int>> tiles;
};

#endif // MAPLOADER_HPP
