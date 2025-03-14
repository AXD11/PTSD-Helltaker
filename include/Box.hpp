#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Wall.hpp"
#include "Util/Logger.hpp"


class Box : public Util::GameObject {

public:
    Box(const std::string image);

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetImage(std::string image) { m_Drawable = std::make_shared<Util::Image>(image); }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    bool IsColliding(const std::shared_ptr<Wall>& other, int position) const;

    glm::vec2 GetCenter() const { return center; }

    void MoveUp(int moveStep) { 
        m_Transform.translation.y += moveStep;
        SetCenter();
    }

    void MoveDown(int moveStep) { 
        m_Transform.translation.y -= moveStep;
        SetCenter();
    }

    void MoveRight(int moveStep) {
        m_Transform.translation.x += moveStep;
        SetCenter();
    }

    void MoveLeft(int moveStep) { 
        m_Transform.translation.x -= moveStep;
        SetCenter();
    }

private:
    glm::vec2 center;
};

#endif
