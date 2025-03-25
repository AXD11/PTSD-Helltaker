#ifndef APP_HPP
#define APP_HPP

#include "Box.hpp"
#include "Hero.hpp" 
#include "MapLoader.hpp"
#include "Wall.hpp"
#include "pch.hpp" // IWYU pragma: export

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

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    // enum class Phase {
    //     CHANGE_CHARACTER_IMAGE,
    //     ABLE_TO_MOVE,
    //     COLLIDE_DETECTION,
    //     BEE_ANIMATION,
    //     OPEN_THE_DOORS,
    //     COUNTDOWN,
    // };


    State m_CurrentState = State::START;

    Util::Renderer m_Root;

    std::shared_ptr<Hero> m_Hero;

    std::shared_ptr<AnimatedCharacter> heroStandby;

    std::shared_ptr<AnimatedCharacter> heroMove;

    std::shared_ptr<AnimatedCharacter> heroKick;

    std::shared_ptr<Wall> m_Wall;

    std::shared_ptr<Box> m_Box;

    MapLoader m_MapLoader;

    std::vector<std::shared_ptr<Tile>> testPtr;


    bool m_EnterDown = false;
    bool m_Up = false;
    bool m_Down = false;
    bool m_Left = false;
    bool m_Right = false;
    int moveStep = 100;
};

#endif
