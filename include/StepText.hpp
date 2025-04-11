#ifndef STEPTEXT_HPP
#define STEPTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class StepText : public Util::GameObject {
public:
    StepText():GameObject(std::make_unique<Util::Text>("/Users/linshengjie/Desktop/PTSD-Helltaker/Resources/fonts/Attack.ttf", 50, "Hello World"), 100){
        m_Transform.translation = {0.0F, -270.F};
    }
};


#endif //TASKTEXT_HPP
