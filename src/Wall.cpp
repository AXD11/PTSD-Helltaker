#include "Wall.hpp"
#include "Util/Logger.hpp"

Wall::Wall(const std::string image) {
    m_Drawable = std::make_shared<Util::Image>(image);
    SetCenter();
    // LOG_DEBUG("Wall center:");
    // LOG_INFO(center);
}