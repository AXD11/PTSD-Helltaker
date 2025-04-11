#include "Box.hpp"

Box::Box() : Tile(GA_RESOURCE_DIR"/Image/Box/box.png")
{
}

bool Box::IsColliding(const std::shared_ptr<Wall>& other, int position) const {
    switch (position) {
        case 1:
            if(glm::vec2(GetCenter().x, GetCenter().y + 100) == other->GetCenter())
                return true;
            break;
        case 2:
            if(glm::vec2(GetCenter().x, GetCenter().y - 100) == other->GetCenter())
                return true;
            break;
        case 3:
            if(glm::vec2(GetCenter().x - 100, GetCenter().y) == other->GetCenter())
                return true;
            break;
        case 4:
            if(glm::vec2(GetCenter().x + 100, GetCenter().y) == other->GetCenter())
                return true;
            break;
        default:
            break;
    }
    return false;
}

bool Box::IsColliding(const std::shared_ptr<Box>& other, int position) const {
    switch (position) {
        case 1:
            if(glm::vec2(GetCenter().x, GetCenter().y + 100) == other->GetCenter())
                return true;
            break;
        case 2:
            if(glm::vec2(GetCenter().x, GetCenter().y - 100) == other->GetCenter())
                return true;
            break;
        case 3:
            if(glm::vec2(GetCenter().x - 100, GetCenter().y) == other->GetCenter())
                return true;
            break;
        case 4:
            if(glm::vec2(GetCenter().x + 100, GetCenter().y) == other->GetCenter())
                return true;
            break;
        default:
            break;
    }
    return false;
}

bool Box::CanMove(int position, const std::vector<std::shared_ptr<Tile>>& tiles){
    for (const auto& tile : tiles) {
        if (auto box = std::dynamic_pointer_cast<Box>(tile)) {
            if (IsColliding(box, position)) {
                return false;
            }
        }
        if (auto wall = std::dynamic_pointer_cast<Wall>(tile)) {
            if (IsColliding(wall, position)) {
                return false;
            }
        }
    }
    return true;
}