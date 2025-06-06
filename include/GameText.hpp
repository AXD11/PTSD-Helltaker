#ifndef GAMETEXT_HPP
#define GAMETEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <glm/fwd.hpp>
#include <string>

class GameText : public Util::GameObject {
public:
    GameText(std::string text, glm::vec2 position):GameObject(std::make_unique<Util::Text>(GA_RESOURCE_DIR"/Font/Attack.ttf", 50, text, Util::Color::FromName(Util::Colors::WHITE)), 97){
        // m_Transform.translation = {-685.0F, -300.F};
        m_Transform.translation = position;
    }

    void SetText(int text){
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(std::to_string(text));
    }
};


#endif //TASKTEXT_HPP
