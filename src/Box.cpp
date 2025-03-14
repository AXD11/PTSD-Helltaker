#include "Box.hpp"
#include "Util/Logger.hpp"

Box::Box(const std::string image) {
    m_Drawable = std::make_shared<Util::Image>(image);
    SetCenter();
    LOG_DEBUG("Box center:");
    LOG_INFO(center);
    LOG_DEBUG("Box position:");
    LOG_INFO(this->GetPosition());
}

bool Box::IsColliding(const std::shared_ptr<Wall>& other, int position) const {
    switch (position) {
        case 1:
            if(glm::vec2(center.x, center.y + 100) == other->GetCenter())
                return true;
            break;
        case 2:
            if(glm::vec2(center.x, center.y - 100) == other->GetCenter())
                return true;
            break;
        case 3:
            if(glm::vec2(center.x - 100, center.y) == other->GetCenter())
                return true;
            break;
        case 4:
            if(glm::vec2(center.x + 100, center.y) == other->GetCenter())
                return true;
            break;
        default:
            break;
    }
    return false;
}