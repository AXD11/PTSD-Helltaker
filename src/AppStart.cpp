#include "AnimatedCharacter.hpp"
#include "App.hpp"

#include "Util/Logger.hpp"
#include "Wall.hpp"
#include "Floor.hpp"
#include <memory>
#include <vector>

void App::Start() {
    LOG_TRACE("Start");

    m_MapLoader.loadMap(GA_RESOURCE_DIR"/Map/Map1.json");
    m_MapLoader.printMap();

    auto tmp = m_MapLoader.GetMap();
    int tmpInt1, tmpInt2 = 0;
    
    testPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
    floorPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());


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

    m_Wall = std::make_shared<Wall>();
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
        LOG_DEBUG("Loading Map...");
        for (int j = 0; j < m_MapLoader.getWidth(); ++j) {
            floorPtr[j + i * m_MapLoader.getWidth()] = std::make_shared<Floor>();
            floorPtr[j + i * m_MapLoader.getWidth()]->SetPosition({-500 + 100 * j,600 - 100 * i});
            floorPtr[j + i * m_MapLoader.getWidth()]->SetVisible(true);
            floorPtr[j + i * m_MapLoader.getWidth()]->SetZIndex(0);
            m_Root.AddChild(floorPtr[j + i * m_MapLoader.getWidth()]);
        }
        // break;
    }

    tmpInt1 = 0;
    tmpInt2 = 0;
    for (const auto& row : tmp) {
        LOG_DEBUG("Loading Map...");
        for (int tile : row) {
            LOG_DEBUG(tile);
            switch (tile) {
                // case 0:
                //     // LOG_DEBUG("Case 0");
                //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Floor>();
                //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({-500 + 100 * tmpInt1,600 - 100 * tmpInt2});
                //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
                //     testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(0);
                //     m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
                //     break;
                case 1:
                    // LOG_DEBUG("Case 0");
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Wall>();
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({-500 + 100 * tmpInt1,600 - 100 * tmpInt2});
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(5);
                    m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
                    break;
                case 2:
                    // LOG_DEBUG("Case 1");
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()] = std::make_shared<Box>();
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetPosition({-500 + 100 * tmpInt1, 600 - 100 * tmpInt2});
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetVisible(true);
                    testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]->SetZIndex(1);
                    m_Root.AddChild(testPtr[tmpInt1 + tmpInt2 * m_MapLoader.getWidth()]);
                    break;
                case 3:
                    m_Hero->SetPosition({-500 + 100 * tmpInt1, 600 - 100 * tmpInt2});
                    break;
                default:
                    // LOG_DEBUG("Case default");
                    break;
            }
            tmpInt1++;
        }
        // break;
        LOG_DEBUG("-----------------");
        tmpInt2++;
        tmpInt1 = 0;
    }
    // m_Wall->SetPosition({ m_Hero->GetPosition().x + 200, m_Hero->GetPosition().y});
    // m_Box->SetPosition({ m_Hero->GetPosition().x + 100, m_Hero->GetPosition().y});
    m_CurrentState = State::UPDATE;
}
