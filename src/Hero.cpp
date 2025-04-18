#include "Hero.hpp"
#include "AnimatedCharacter.hpp"
#include "Box.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>

Hero::Hero(const std::string image, std::shared_ptr<AnimatedCharacter>& standbyAnimation, std::shared_ptr<AnimatedCharacter>& moveAnimation, std::shared_ptr<AnimatedCharacter>& kickAnimation, std::shared_ptr<AnimatedCharacter>& deadAnimation)
: currentState(HeroState::STANDBY),
  standbyAnimation(standbyAnimation),
  moveAnimation(moveAnimation),
  kickAnimation(kickAnimation),
  deadAnimation(deadAnimation)
{
    SetImage(image);
    SetCenter();
    stepText = std::make_shared<StepText>(step);
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

bool Hero::IsColliding(const std::shared_ptr<Enemy>& other, int position) const {
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

bool Hero::MeetEnemy(int position, const std::vector<std::shared_ptr<Enemy>>& enemies, const std::vector<std::shared_ptr<Tile>>& tiles){
    for (const auto& skelton : enemies) {
        if (skelton == nullptr) continue;
        skelton->SetCenter();
        if (IsColliding(skelton, position)) {
            GetKickAnimation()->SetCurrentFrame(0);
            SetState(HeroState::KICK);
            GetKickAnimation()->Play();
            if (skelton->CanMove(position, tiles)){
                skelton->GetBeKickedAnimation()->SetCurrentFrame(0);
                skelton->SetState(EnemyState::BEKICKED);
                skelton->GetBeKickedAnimation()->Play();
                skelton->Move(100, position);
            }
            SetLevelStep(step - 1);
            return true;
        }
    }
    return false;
}

bool Hero::CanMove(int position, const std::vector<std::shared_ptr<Tile>>& tiles){
    for (const auto& tile : tiles) {
        if (auto box = std::dynamic_pointer_cast<Box>(tile)) {
            if (IsColliding(box, position)) {
                GetKickAnimation()->SetCurrentFrame(0);
                SetState(HeroState::KICK);
                GetKickAnimation()->Play();
                if (box->CanMove(position, tiles)) {
                    // LOG_DEBUG("Change to Kick");
                    box->Move(100, position);
                }
                SetLevelStep(step - 1);
                return false;
            }
        }
        else if (auto wall = std::dynamic_pointer_cast<Wall>(tile)) {
            if (IsColliding(wall, position)) {
                
                return false;
            }
        }
    }
    return true;
}

void Hero::SetState(HeroState newState) {
    if (currentState == newState) return;


    // LOG_DEBUG("Is Standby? ");
    // LOG_DEBUG(newState == HeroState::STANDBY);
    // LOG_DEBUG("Is Move? ");
    // LOG_DEBUG(newState == HeroState::MOVE);
    // LOG_DEBUG("Is Kick? ");
    // LOG_DEBUG(newState == HeroState::KICK);
    currentState = newState;
    standbyAnimation->SetVisible(newState == HeroState::STANDBY);
    moveAnimation->SetVisible(newState == HeroState::MOVE);
    kickAnimation->SetVisible(newState == HeroState::KICK);
    deadAnimation->SetVisible(newState == HeroState::DEAD);
}

// void Hero::update() {
//     if (currentState == HeroState::STANDBY) {
//         standByAnimation.SetPosition(m_Transform.translation);
//     } else if (currentState == HeroState::MOVE) {
//         moveAnimation.SetPosition(m_Transform.translation);
//     }
// }
