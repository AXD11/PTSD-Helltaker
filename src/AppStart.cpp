#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Enemy.hpp"
#include "Util/Logger.hpp"
#include "Util/Text.hpp"
#include "Wall.hpp"
#include "Floor.hpp"
#include <memory>
#include <vector>

void App::Start() {
    LOG_TRACE("Start");


    m_Background = std::make_shared<Background>(GA_RESOURCE_DIR"/Image/Other/Step.png");
    m_Background->SetVisible(true);
    m_Background->SetZIndex(97);
    m_Background->SetPosition({-660,-220});
    m_Background->GetTransform().scale = {-1, 1};
    m_Root.AddChild(m_Background);

    blackScreen = std::make_shared<Background>(GA_RESOURCE_DIR"/Image/Other/black.png");
    blackScreen->SetVisible(false);
    blackScreen->SetZIndex(98);
    blackScreen->SetPosition({0, 0});
    m_Root.AddChild(blackScreen);



    m_MapLoader.loadMap(GA_RESOURCE_DIR"/Map/Map1.json");
    // m_MapLoader.printMap();

    auto tmp = m_MapLoader.GetMap();
    // int tmpInt1, tmpInt2 = 0;
    
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
    LOG_DEBUG("EyeCatch Images Size: ");
    LOG_DEBUG(eyeCatchImages.size());
    eyeCatch = std::make_shared<AnimatedCharacter>(eyeCatchImages, 66, false);
    eyeCatch->SetZIndex(100);
    eyeCatch->SetVisible(false);
    eyeCatch->SetPosition({0, 0});
    m_Root.AddChild(eyeCatch);

    for (int i = 0; i < 12; ++i) {
        heroStandbyImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Standby/hero" + std::to_string(i + 1) + ".png");
    }
    LOG_DEBUG("hero Images Size: ");
    LOG_DEBUG(heroStandbyImages.size());
    // AnimatedCharacter heroStandby(heroStandbyImages, 83, true);
    heroStandby = std::make_shared<AnimatedCharacter>(heroStandbyImages, 83, true);
    heroStandby->SetZIndex(10);
    heroStandby->SetVisible(true);
    m_Root.AddChild(heroStandby);

    for (int i = 0; i < 6; ++i) {
        heroMoveImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Move/move" + std::to_string(i + 1) + ".png");
    }

    // AnimatedCharacter heroMove(heroMoveImages, 166, false);
    heroMove = std::make_shared<AnimatedCharacter>(heroMoveImages, 60, false);
    heroMove->SetZIndex(10);
    heroMove->SetVisible(false);
    m_Root.AddChild(heroMove);

    for (int i = 0; i < 12; ++i) {
        heroKickImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Kick/kick" + std::to_string(i + 1) + ".png");
    }

    // AnimatedCharacter heroKick(heroKickImages, 166, false);
    heroKick = std::make_shared<AnimatedCharacter>(heroKickImages, 20, false);
    heroKick->SetZIndex(10);
    heroKick->SetVisible(false);
    m_Root.AddChild(heroKick);

    for (int i = 0; i < 18; ++i) {
        heroDeadImages.emplace_back(GA_RESOURCE_DIR"/Image/Hero/Dead/dead" + std::to_string(i + 1) + ".png");
    }

    heroDead = std::make_shared<AnimatedCharacter>(heroDeadImages, 20, false);
    heroDead->SetZIndex(100);
    heroDead->SetVisible(false);
    m_Root.AddChild(heroDead);

    m_Hero = std::make_shared<Hero>(GA_RESOURCE_DIR"/Image/Hero/Sprite.png", heroStandby, heroMove, heroKick, heroDead);
    m_Hero->SetZIndex(5);
    m_Hero->SetVisible(true);
    m_Hero->SetPosition(glm::vec2(-50, 50));
    heroStandby->SetPosition(m_Hero->GetPosition());
    m_Root.AddChild(m_Hero);


    // m_Wall = std::make_shared<Wall>();
    // m_Wall->SetZIndex(1);
    // m_Wall->SetVisible(true);
    // m_Wall->SetPosition({ m_Hero->GetPosition().x, m_Hero->GetPosition().y + 100});
    // m_Wall->SetCenter();
    // m_Root.AddChild(m_Wall);

    m_Box = std::make_shared<Box>();
    // m_Box->SetZIndex(1);
    // m_Box->SetVisible(true);
    // m_Box->SetPosition({ m_Hero->GetPosition().x + 100, m_Hero->GetPosition().y});
    // m_Box->SetCenter();
    // m_Root.AddChild(m_Box);

    for (int i = 0; i < m_MapLoader.getHeight(); ++i) {
        // LOG_DEBUG("Loading FLoor...");
        for (int j = 0; j < m_MapLoader.getWidth(); ++j) {
            floorPtr[j + i * m_MapLoader.getWidth()] = std::make_shared<Floor>();
            floorPtr[j + i * m_MapLoader.getWidth()]->SetPosition({init_position.x + 100 * j,init_position.y - 100 * i});
            floorPtr[j + i * m_MapLoader.getWidth()]->SetVisible(true);
            floorPtr[j + i * m_MapLoader.getWidth()]->SetZIndex(0);
            m_Root.AddChild(floorPtr[j + i * m_MapLoader.getWidth()]);
        }
        // break;
    }

    m_MapLoader.SetMap(init_position, testPtr, enemyPtr, m_Root, m_Hero, m_Devil);

    // tmpInt1 = 0;
    // tmpInt2 = 0;
    // for (const auto& row : tmp) {
    //     LOG_DEBUG("Loading Map...");
    //     for (int tile : row) {
    //         LOG_DEBUG(tile);
    //         switch (tile) {
    //             // case 0:
    //             //     // LOG_DEBUG("Case 0");
    //             //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Floor>();
    //             //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({-500 + 100 * tmpInt1,600 - 100 * tmpInt2});
    //             //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
    //             //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(0);
    //             //     m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
    //             //     break;
    //             case 1:
    //                 // LOG_DEBUG("Case 0");
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Wall>();
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({init_position.x + 100 * tmpInt1,init_position.y - 100 * tmpInt2});
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(5);
    //                 m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
    //                 break;
    //             case 2:
    //                 // LOG_DEBUG("Case 1");
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Box>();
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
    //                 testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(1);
    //                 m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
    //                 break;
    //             case 3:
    //                 m_Hero->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
    //                 m_Hero->SetLevelStep(m_MapLoader.getStep());
    //                 break;
    //             case 4:
    //                 LOG_DEBUG("Case 4");
    //                 enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Enemy>();
    //                 enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({init_position.x + 100 * tmpInt1, init_position.y - 100 * tmpInt2});
    //                 enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
    //                 enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(4);
    //                 m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
    //                 m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->GetStandbyAnimation());
    //                 m_Root.AddChild(enemyPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->GetBeKickedAnimation());
    //                 // LOG_DEBUG("index");
    //                 // LOG_DEBUG(tmpInt1 + tmpInt2 * m_MapLoader.getWidth());
    //                 // LOG_DEBUG("````");
    //                 break;
    //             default:
    //                 // LOG_DEBUG("Case default");
    //                 break;
    //         }
    //         tmpInt1++;
    //     }
    //     // break;
    //     LOG_DEBUG("-----------------");
    //     tmpInt2++;
    //     tmpInt1 = 0;
    // }
    
    // LOG_DEBUG(enemyPtr[12]->GetCenter());
    // m_Wall->SetPosition({ m_Hero->GetPosition().x + 200, m_Hero->GetPosition().y});
    // m_Box->SetPosition({ m_Hero->GetPosition().x + 100, m_Hero->GetPosition().y});
    m_Root.AddChild(m_Hero->GetChild());
    m_CurrentState = State::UPDATE;
}
