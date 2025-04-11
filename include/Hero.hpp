#ifndef HERO_HPP
#define HERO_HPP

#include <memory>
#include <string>

#include "AnimatedCharacter.hpp"
#include "StepText.hpp"
#include "Util/Logger.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Enemy.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


enum class HeroState {
    STANDBY,
    MOVE,
    KICK,
};

enum class Direction {
    Up,
    Down,
    Left,
    Right,
};

class Hero : public Util::GameObject {

public:
    Hero(const std::string image, const std::shared_ptr<AnimatedCharacter>& standbyAnimation, const std::shared_ptr<AnimatedCharacter>& moveAnimation, const std::shared_ptr<AnimatedCharacter>& kickAnimation);

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
        standbyAnimation->SetPosition(m_Transform.translation);
        moveAnimation->SetPosition(m_Transform.translation);
        kickAnimation->SetPosition(m_Transform.translation);
    }

    [[nodiscard]] HeroState getState() const;

    void SetImage(std::string image) { m_Drawable = std::make_shared<Util::Image>(image); }

    void SetState(HeroState state);

    HeroState GetCurrentState() {return currentState; }

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    void MoveUp(int moveStep) { 
        SetPosition(glm::vec2(m_Transform.translation.x, m_Transform.translation.y + moveStep));
        SetCenter();
        // kickAnimation->IfAnimationEnds();
    }

    void MoveDown(int moveStep) { 
        SetPosition(glm::vec2(m_Transform.translation.x, m_Transform.translation.y - moveStep));
        SetCenter();
    }

    void MoveRight(int moveStep) {
        SetPosition(glm::vec2(m_Transform.translation.x + moveStep, m_Transform.translation.y));
        SetCenter();
    }

    void MoveLeft(int moveStep) { 
        SetPosition(glm::vec2(m_Transform.translation.x - moveStep, m_Transform.translation.y));
        SetCenter();
    }

    bool CanMove(int position, const std::vector<std::shared_ptr<Tile>>& tiles);

    bool MeetEnemy(int position, const std::vector<std::shared_ptr<Enemy>>& enemies, const std::vector<std::shared_ptr<Tile>>& tiles);

    bool IsColliding(const std::shared_ptr<Wall>& other, int position) const;

    bool IsColliding(const std::shared_ptr<Box>& other, int position) const;

    bool IsColliding(const std::shared_ptr<Enemy>& other, int position) const;

    std::shared_ptr<AnimatedCharacter> GetStandbyAnimation() const { return standbyAnimation; }

    std::shared_ptr<AnimatedCharacter> GetMoveAnimation() const { return moveAnimation; }

    std::shared_ptr<AnimatedCharacter> GetKickAnimation() const { return kickAnimation; }

    glm::vec2 GetCenter() const { return center; }

    std::shared_ptr<Util::GameObject> GetChild(){
        return stepText;
    }

private:
    HeroState currentState;
    glm::vec2 center;
    const std::shared_ptr<AnimatedCharacter>& standbyAnimation;
    const std::shared_ptr<AnimatedCharacter>& moveAnimation;
    const std::shared_ptr<AnimatedCharacter>& kickAnimation;
    std::shared_ptr<StepText> stepText;
};

#endif //HERO_HPP
