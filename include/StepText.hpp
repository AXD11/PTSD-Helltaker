#ifndef STEPTEXT_HPP
#define STEPTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include <string>

class StepText : public Util::GameObject {
public:
    StepText(int step):GameObject(std::make_unique<Util::Text>("/Users/linshengjie/Desktop/PTSD-Helltaker/Resources/fonts/Attack.ttf", 50, std::to_string(step), Util::Color::FromName(Util::Colors::WHITE)), 100){
        m_Transform.translation = {-685.0F, -300.F};
    }

    void SetStepText(int step){
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(std::to_string(step));
    }
};


#endif //TASKTEXT_HPP
