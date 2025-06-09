#include "Enemy.hpp"
#include "AnimatedCharacter.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include <glm/fwd.hpp>
#include <memory>

// #include <iostream>


Enemy::Enemy(): currentState(EnemyState::STANDBY)
{
    std::vector<std::string> enemyStandbyImages;
    std::vector<std::string> enemyBeKickedImages;

    for (int i = 0; i < 12; ++i) {
        enemyStandbyImages.emplace_back(GA_RESOURCE_DIR"/Image/Enemy/Standby/enemy" + std::to_string(i + 1) + ".png");
    }

    for (int i = 0; i < 6; ++i) {
        enemyBeKickedImages.emplace_back(GA_RESOURCE_DIR"/Image/Enemy/BeKicked/beKicked" + std::to_string(i + 1) + ".png");
    }

    standbyAnimation = std::make_shared<AnimatedCharacter>(enemyStandbyImages, true, 83, true);
    standbyAnimation->SetZIndex(4);
    standbyAnimation->SetVisible(true);

    beKickedAnimation = std::make_shared<AnimatedCharacter>(enemyBeKickedImages, true, 83, false);
    beKickedAnimation->SetZIndex(4);
    beKickedAnimation->SetVisible(false);

    beKickedEffects = std::make_shared<Util::SFX>(GA_RESOURCE_DIR"/Audio/enemy_kick_01.wav");
    beKickedEffects->SetVolume(50);

    deathEffects = std::make_shared<Util::SFX>(GA_RESOURCE_DIR"/Audio/enemy_die_03.wav");
    deathEffects->SetVolume(50);

    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR"/Image/Enemy/Sprite.png");
    SetCenter();

}

bool Enemy::IsColliding(const std::shared_ptr<Tile>& other, int position) const {
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
    return false;
}

bool Enemy::IsColliding(const std::shared_ptr<Enemy>& other, int position) const {
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

bool Enemy::CanMove(int position, const std::vector<std::shared_ptr<Tile>>& tiles, const std::vector<std::shared_ptr<Enemy>>& enemies) {
    for (const auto& tile : tiles) {
        if (tile == nullptr) continue;
        if (IsColliding(tile, position)) {
            SetState(EnemyState::DEAD);
            this->SetPosition(glm::vec2(-10000, -10000));

            deathEffects->Play();
            return false;
        }
    }
    for (const auto& enemy : enemies) {
        if (enemy == nullptr) continue;
        enemy->SetCenter();
        if (IsColliding(enemy, position)) {
            SetState(EnemyState::DEAD);
            this->SetPosition(glm::vec2(-10000, -10000));

            deathEffects->Play();
            return false;
        }
    }
    return true;
}

void Enemy::SetState(EnemyState newState) {
    if (currentState == newState) return;


    // LOG_DEBUG("Is Standby? ");
    // LOG_DEBUG(newState == EnemyState::STANDBY);
    // LOG_DEBUG("Is BeKick? ");
    // LOG_DEBUG(newState == EnemyState::BEKICKED);
    // LOG_DEBUG("Is Dead? ");
    // LOG_DEBUG(newState == EnemyState::DEAD);
    // currentState = newState;

    currentState = newState;
    standbyAnimation->SetVisible(newState == EnemyState::STANDBY);
    beKickedAnimation->SetVisible(newState == EnemyState::BEKICKED);
    
}

// void Hero::update() {
//     if (currentState == HeroState::STANDBY) {
//         standByAnimation.SetPosition(m_Transform.translation);
//     } else if (currentState == HeroState::MOVE) {
//         moveAnimation.SetPosition(m_Transform.translation);
//     }
// }
