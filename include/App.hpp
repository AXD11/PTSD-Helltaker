#ifndef APP_HPP
#define APP_HPP

#include "AnimatedCharacter.hpp"
#include "Background.hpp"
// #include "Box.hpp"
#include "Devil.hpp"
#include "Enemy.hpp"
#include "Hero.hpp" 
#include "Key.hpp"
#include "LockBox.hpp"
#include "MapLoader.hpp"
#include "GameText.hpp"
#include "Floor.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/SFX.hpp"
#include "Util/Renderer.hpp"
#include <memory>
#include <vector>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End();

private:
    void ValidTask();

private:

    State m_CurrentState = State::START;

    Util::Renderer m_Root;

    std::shared_ptr<Hero> m_Hero;

    std::shared_ptr<AnimatedCharacter> heroStandby;

    std::shared_ptr<AnimatedCharacter> heroMove;

    std::shared_ptr<AnimatedCharacter> heroKick;

    std::shared_ptr<AnimatedCharacter> heroDead;

    MapLoader m_MapLoader;

    std::vector<std::shared_ptr<Tile>> testPtr;

    std::vector<std::shared_ptr<Floor>> floorPtr;

    std::vector<std::shared_ptr<Enemy>> enemyPtr;

    std::shared_ptr<Background> m_Background;

    std::shared_ptr<Background> m_Background2;

    std::shared_ptr<Background> blackScreen;

    std::shared_ptr<Devil> m_Devil;

    std::shared_ptr<AnimatedCharacter> eyeCatch;

    std::shared_ptr<GameText> levelText;

    std::shared_ptr<Key> m_Key;

    std::shared_ptr<Util::SFX> m_SFX;

    std::shared_ptr<Util::SFX> m_Soundffects;

    bool m_EnterDown = false;
    bool m_Up = false;
    bool m_Down = false;
    bool m_Left = false;
    bool m_Right = false;
    int stepLock = 0;
    int moveStep = 100;
    bool reset = false;
    int currentLevel = 1;
    bool nextLevel = false;
    glm::vec2 init_position;

    bool finish = false;
};

#endif
