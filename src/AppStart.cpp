#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "MapLoader.hpp"
#include "Util/Logger.hpp"
// #include "Util/Text.hpp"
#include <memory>
#include <vector>

void App::Start() {
    LOG_TRACE("Start");


    m_Background = std::make_shared<Background>(GA_RESOURCE_DIR"/Image/Other/Step.png");
    m_Background->SetVisible(true);
    m_Background->SetZIndex(96);
    m_Background->SetPosition({-660,-220});
    m_Background->GetTransform().scale = {-1, 1};
    m_Root.AddChild(m_Background);

    blackScreen = std::make_shared<Background>(GA_RESOURCE_DIR"/Image/Other/black.png");
    blackScreen->SetVisible(false);
    blackScreen->SetZIndex(98);
    blackScreen->SetPosition({0, 0});
    m_Root.AddChild(blackScreen);



    m_MapLoader.loadMap(GA_RESOURCE_DIR"/Map/Map" + std::to_string(currentLevel) + ".json");

    m_MapLoader.PrintMap();

    auto tmp = m_MapLoader.GetMap();
    
    init_position = glm::vec2(50 - 100 * m_MapLoader.getWidth()/2, -50 + 100 * m_MapLoader.getHeight()/2);

    testPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
    floorPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
    enemyPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());


    std::vector<std::string> heroStandbyImages;

    std::vector<std::string> heroMoveImages;

    std::vector<std::string> heroKickImages;

    std::vector<std::string> heroDeadImages;

    std::vector<std::string> eyeCatchImages;
    
    heroStandbyImages.reserve(12);
    heroMoveImages.reserve(6);
    heroKickImages.reserve(12);
    heroDeadImages.reserve(18);
    eyeCatchImages.reserve(29);

    for (int i = 0; i < 29; ++i) {
        eyeCatchImages.emplace_back(GA_RESOURCE_DIR"/Image/Other/Eyecatch/eyecatch" + std::to_string(i + 1) + ".png");
    }

    eyeCatch = std::make_shared<AnimatedCharacter>(eyeCatchImages, true, 66, false);
    eyeCatch->SetZIndex(100);
    eyeCatch->SetVisible(false);
    eyeCatch->SetPosition({0, 0});
    m_Root.AddChild(eyeCatch);

    for (int i = 0; i < 12; ++i) {
        heroStandbyImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Standby/hero" + std::to_string(i + 1) + ".png");
    }

    heroStandby = std::make_shared<AnimatedCharacter>(heroStandbyImages, true, 83, true);
    heroStandby->SetZIndex(10);
    heroStandby->SetVisible(true);
    m_Root.AddChild(heroStandby);

    for (int i = 0; i < 6; ++i) {
        heroMoveImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Move/move" + std::to_string(i + 1) + ".png");
    }

    heroMove = std::make_shared<AnimatedCharacter>(heroMoveImages, true, 66, false);
    heroMove->SetZIndex(10);
    heroMove->SetVisible(false);
    m_Root.AddChild(heroMove);

    for (int i = 0; i < 12; ++i) {
        heroKickImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Kick/kick" + std::to_string(i + 1) + ".png");
    }

    heroKick = std::make_shared<AnimatedCharacter>(heroKickImages, true, 20, false);
    heroKick->SetZIndex(10);
    heroKick->SetVisible(false);
    m_Root.AddChild(heroKick);

    for (int i = 0; i < 18; ++i) {
        heroDeadImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Dead/dead" + std::to_string(i + 1) + ".png");
    }

    heroDead = std::make_shared<AnimatedCharacter>(heroDeadImages, true, 20, false);
    heroDead->SetZIndex(100);
    heroDead->SetVisible(false);
    m_Root.AddChild(heroDead);

    m_Hero = std::make_shared<Hero>(GA_RESOURCE_DIR"/Image/Hero/Sprite.png", heroStandby, heroMove, heroKick, heroDead);
    m_Hero->SetZIndex(5);
    m_Hero->SetVisible(true);
    m_Hero->SetPosition(glm::vec2(-50, 50));
    heroStandby->SetPosition(m_Hero->GetPosition());
    m_Root.AddChild(m_Hero);

    m_MapLoader.SetMap(init_position, floorPtr, testPtr, enemyPtr, m_Root, m_Hero, m_Devil);

    m_Root.AddChild(m_Hero->GetChild());
    m_CurrentState = State::UPDATE;

    stepLock = m_Hero->GetStep();
}
