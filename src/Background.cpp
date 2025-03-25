#include "Background.hpp"

Background::Background(const std::string image) {
    m_Drawable = std::make_shared<Util::Image>(image);
}