#include "Tile.hpp"

Tile::Tile(const std::string image)
{
    m_Drawable = std::make_shared<Util::Image>(image);
    SetCenter();
}