#ifndef WALL_HPP
#define WALL_HPP

#include <memory>
#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"


class Wall : public Util::GameObject {

public:
    Wall(const std::string image);

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetImage(std::string image) { m_Drawable = std::make_shared<Util::Image>(image); }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    glm::vec2 GetCenter() const { return center; }

private:
    glm::vec2 center;
};

#endif
