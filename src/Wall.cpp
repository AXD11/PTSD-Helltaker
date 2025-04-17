#include "Wall.hpp"
#include <string>

Wall::Wall(std::string name): Tile(GA_RESOURCE_DIR"/Image/Wall/" + name + ".png")
{
}