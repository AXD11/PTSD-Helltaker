#ifndef TILE_HPP
#define TILE_HPP

#include "Util/GameObject.hpp"
#include <string>
#include "Util/Image.hpp"

class Tile : public Util::GameObject {
public:
    Tile(const std::string image);

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { 
        m_Transform.translation = Position;
        SetCenter();
    }

    void SetImage(std::string image) { m_Drawable = std::make_shared<Util::Image>(image); }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    glm::vec2 GetCenter() const { return center; }

private:
    std::string image;
    glm::vec2 center;
};

#endif