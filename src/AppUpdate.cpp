#include "App.hpp"

#include "Hero.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */


    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }


    if (m_Up) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (m_Hero->CanMove(Direction::Up, testPtr)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveUp(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }

    }
    m_Up = Util::Input::IsKeyDown(Util::Keycode::W);

    if (m_Down) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (m_Hero->CanMove(Direction::Down, testPtr)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveDown(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }

    }
    m_Down = Util::Input::IsKeyDown(Util::Keycode::S);

    if (m_Left) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (m_Hero->CanMove(Direction::Left, testPtr)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveLeft(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
    }
    m_Left = Util::Input::IsKeyDown(Util::Keycode::A);

    if (m_Right) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (m_Hero->CanMove(Direction::Right, testPtr)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveRight(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
    }
    m_Right = Util::Input::IsKeyDown(Util::Keycode::D);


    // (Util::Input::IsKeyUp(Util::Keycode::W) || 
    //     Util::Input::IsKeyUp(Util::Keycode::S) || 
    //     Util::Input::IsKeyUp(Util::Keycode::A) || 
    //     Util::Input::IsKeyUp(Util::Keycode::D)) &&
    if ((m_Hero->GetMoveAnimation()->IfAnimationEnds() || 
         m_Hero->GetKickAnimation()->IfAnimationEnds())&&
         m_Hero->GetCurrentState() != HeroState::STANDBY) 
    {
        m_Hero->SetState(HeroState::STANDBY);
        m_Hero->GetStandbyAnimation()->SetPosition(m_Hero->GetPosition());
        LOG_DEBUG(m_Hero->GetStandbyAnimation()->IsLooping());
    }

    m_Root.Update();
}
