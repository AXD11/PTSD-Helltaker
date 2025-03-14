#include "Hero.hpp"
#include "AnimatedCharacter.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>

Hero::Hero(const std::string image, const std::shared_ptr<AnimatedCharacter>& standbyAnimation, const std::shared_ptr<AnimatedCharacter>& moveAnimation, const std::shared_ptr<AnimatedCharacter>& kickAnimation)
: currentState(HeroState::STANDBY),
  standbyAnimation(standbyAnimation),
  moveAnimation(moveAnimation),
  kickAnimation(kickAnimation)
{
    SetImage(image);
    SetCenter();
}

bool Hero::IsColliding(const std::shared_ptr<Wall>& other, int position) const {
    switch (position) {
        case 1:
        // LOG_DEBUG(1);
            if(glm::vec2(center.x, center.y + 100) == other->GetCenter())
                return true;
            break;
        case 2:
        // LOG_DEBUG(2);
            if(glm::vec2(center.x, center.y - 100) == other->GetCenter())
                return true;
            break;
        case 3:
        // LOG_DEBUG(3);
            if(glm::vec2(center.x - 100, center.y) == other->GetCenter())
                return true;
            break;
        case 4:
        // LOG_DEBUG(4);
            if(glm::vec2(center.x + 100, center.y) == other->GetCenter())
                return true;
            break;
        default:
            break;
    }
    // if (this->GetPosition().x - 100 < other->GetPosition().x + other->GetScaledSize().x &&
    //     this->GetPosition().x + this->GetScaledSize().x + 100 > other->GetPosition().x &&
    //     this->GetPosition().y - 100 < other->GetPosition().y + other->GetScaledSize().y &&
    //     this->GetPosition().y + this->GetScaledSize().y + 100> other->GetPosition().y)
    //     return true;
    return false;
}

bool Hero::IsColliding(const std::shared_ptr<Box>& other, int position) const {
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

void Hero::SetState(HeroState newState) {
    if (currentState == newState) return;

    currentState = newState;
    standbyAnimation->SetVisible(newState == HeroState::STANDBY);
    moveAnimation->SetVisible(newState == HeroState::MOVE);
    kickAnimation->SetVisible(newState == HeroState::KICK);
}

// void Hero::update() {
//     if (currentState == HeroState::STANDBY) {
//         standByAnimation.SetPosition(m_Transform.translation);
//     } else if (currentState == HeroState::MOVE) {
//         moveAnimation.SetPosition(m_Transform.translation);
//     }
// }
