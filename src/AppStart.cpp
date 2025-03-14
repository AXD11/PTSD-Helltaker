#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");

    std::vector<std::string> heroStandbyImages;

    std::vector<std::string> heroMoveImages;

    std::vector<std::string> heroKickImages;

    
    heroStandbyImages.reserve(12);
    heroMoveImages.reserve(6);
    heroKickImages.reserve(12);

    for (int i = 0; i < 12; ++i) {
        heroStandbyImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Standby/hero" + std::to_string(i + 1) + ".png");
    }

    // AnimatedCharacter heroStandby(heroStandbyImages, 83, true);
    heroStandby = std::make_shared<AnimatedCharacter>(heroStandbyImages, 83, true);
    heroStandby->SetZIndex(5);
    heroStandby->SetVisible(true);
    m_Root.AddChild(heroStandby);

    for (int i = 0; i < 6; ++i) {
        heroMoveImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Move/move" + std::to_string(i + 1) + ".png");
    }

    // AnimatedCharacter heroMove(heroMoveImages, 166, false);
    heroMove = std::make_shared<AnimatedCharacter>(heroMoveImages, 60, false);
    heroMove->SetZIndex(5);
    heroMove->SetVisible(false);
    m_Root.AddChild(heroMove);

    for (int i = 0; i < 12; ++i) {
        heroKickImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Kick/kick" + std::to_string(i + 1) + ".png");
    }

    // AnimatedCharacter heroKick(heroKickImages, 166, false);
    heroKick = std::make_shared<AnimatedCharacter>(heroKickImages, 20, false);
    heroKick->SetZIndex(5);
    heroKick->SetVisible(false);
    m_Root.AddChild(heroKick);

    m_Hero = std::make_shared<Hero>(GA_RESOURCE_DIR"/Image/Hero/Sprite.png", heroStandby, heroMove, heroKick);
    m_Hero->SetZIndex(5);
    m_Hero->SetVisible(true);
    m_Hero->SetPosition(glm::vec2(-50, 50));
    heroStandby->SetPosition(m_Hero->GetPosition());
    m_Root.AddChild(m_Hero);

    m_Wall = std::make_shared<Wall>(GA_RESOURCE_DIR"/Image/Wall/wall.png");
    m_Wall->SetZIndex(1);
    m_Wall->SetVisible(true);
    m_Wall->SetPosition({ m_Hero->GetPosition().x, m_Hero->GetPosition().y + 100});
    m_Wall->SetCenter();
    m_Root.AddChild(m_Wall);

    m_Box = std::make_shared<Box>(GA_RESOURCE_DIR"/Image/Box/box.png");
    m_Box->SetZIndex(1);
    m_Box->SetVisible(true);
    m_Box->SetPosition({ m_Hero->GetPosition().x + 100, m_Hero->GetPosition().y});
    m_Box->SetCenter();
    m_Root.AddChild(m_Box);

    m_CurrentState = State::UPDATE;
}
