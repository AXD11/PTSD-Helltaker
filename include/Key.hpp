#ifndef KEY_HPP
#define KEY_HPP

#include <Util/GameObject.hpp>
#include "Util/Image.hpp"
#include <string>
#include <memory>


class Key : public Util::GameObject{

public:
    Key(){
        m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR"/Image/Key/key12.png");
    }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { 
        m_Transform.translation = Position;
        SetCenter();
    }

    [[nodiscard]] const glm::vec2& GetCenter() const { return center; }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }
private:
    glm::vec2 center;
};

#endif
