#ifndef DEVIL_HPP
#define DEVIL_HPP

#include <memory>
#include <string>

#include "AnimatedCharacter.hpp"
#include "Util/Logger.hpp"
#include "Wall.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "iostream"


enum class DevilState {
    STANDBY,
};

class Devil : public Util::GameObject {

public:
    Devil(std::string name){
        std::vector<std::string> devilStandbyImages;
        if (name == "Monica") {
            for (int i = 0; i < 12; ++i) {
                devilStandbyImages.emplace_back(GA_RESOURCE_DIR"/Image/Devil/Monica/monica" + std::to_string(i + 1) + ".png");
            }
        } else {
            LOG_ERROR("Devil name is not valid");
        }

        standbyAnimation = std::make_shared<AnimatedCharacter>(devilStandbyImages, true, 83, true);
        standbyAnimation->SetZIndex(4);
        standbyAnimation->SetVisible(true);

        m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR"/Image/Devil/Sprite.png");
        SetCenter();
    }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
        standbyAnimation->SetPosition(m_Transform.translation);
        SetCenter();
    }

    [[nodiscard]] DevilState getState() const;

    // bool IsNearBy(const std::shared_ptr<Hero>& other) {
    //     // std::cout << "Hero: {" << other->GetCenter().x << ", " << other->GetCenter().y << "} Devil: {" << center.x << ", " << center.y << "}" << std::endl;
    //     if (glm::vec2{center.x, center.y + 100} == other->GetCenter()
    //         || glm::vec2{center.x, center.y - 100} == other->GetCenter()
    //         || glm::vec2{center.x - 100, center.y} == other->GetCenter()
    //         || glm::vec2{center.x + 100, center.y} == other->GetCenter()){
    //             // LOG_DEBUG("Devil is near by");
    //             return true;
    //         }
    //     return false;
    // }

    void SetState(DevilState state);

    void SetCenter(){
        center = glm::vec2(this->GetPosition().x + this->GetScaledSize().x / 2, this->GetPosition().y - this->GetScaledSize().y / 2);
    }

    std::shared_ptr<AnimatedCharacter> GetStandbyAnimation() const { return standbyAnimation; }

    glm::vec2 GetCenter() const { return center; }

private:
    glm::vec2 center;
    std::shared_ptr<AnimatedCharacter> standbyAnimation;
};

#endif
