#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>
#include <string>

#include "AnimatedCharacter.hpp"
#include "Util/Logger.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


enum class EnemyState {
    STANDBY,
    BEKICKED,
    DEAD,
};

class Enemy : public Util::GameObject {

public:
    Enemy();

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
        standbyAnimation->SetPosition(m_Transform.translation);
        beKickedAnimation->SetPosition(m_Transform.translation);
    }

    [[nodiscard]] EnemyState getState() const;


    void SetState(EnemyState state);

    EnemyState GetCurrentState() {return currentState; }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    void Move(int moveStep, int position) { 
        switch (position) {
            case 1:
                m_Transform.translation.y += moveStep;
                break;
            case 2:
                m_Transform.translation.y -= moveStep;
                break;
            case 3:
                m_Transform.translation.x -= moveStep;
                break;
            case 4:
                m_Transform.translation.x += moveStep;
                break;
            default:
                break;
        
        }
        SetCenter();
        standbyAnimation->SetPosition(m_Transform.translation);
        beKickedAnimation->SetPosition(m_Transform.translation);
    }

    bool CanMove(int position, const std::vector<std::shared_ptr<Tile>>& tiles);

    bool IsColliding(const std::shared_ptr<Wall>& other, int position) const;

    bool IsColliding(const std::shared_ptr<Box>& other, int position) const;

    std::shared_ptr<AnimatedCharacter> GetStandbyAnimation() const { return standbyAnimation; }

    std::shared_ptr<AnimatedCharacter> GetBeKickedAnimation() const { return beKickedAnimation; }

    glm::vec2 GetCenter() const { return center; }

private:
    EnemyState currentState;
    glm::vec2 center;
    std::shared_ptr<AnimatedCharacter> standbyAnimation;
    std::shared_ptr<AnimatedCharacter> beKickedAnimation;
};

#endif //HERO_HPP
