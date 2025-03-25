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
        if (!m_Hero->IsColliding(m_Wall, 1) && !m_Hero->IsColliding(m_Box, 1)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveUp(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
        else if (m_Hero->IsColliding(m_Box, 1) && !m_Box->IsColliding(m_Wall, 1)) {
            m_Hero->SetState(HeroState::KICK);
            m_Box->MoveUp(moveStep);
            m_Hero->GetKickAnimation()->SetCurrentFrame(0);
            m_Hero->GetKickAnimation()->Play();
        }
    }
    m_Up = Util::Input::IsKeyDown(Util::Keycode::W);

    if (m_Down) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (!m_Hero->IsColliding(m_Wall, 2) && !m_Hero->IsColliding(m_Box, 2)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveDown(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
        else if (m_Hero->IsColliding(m_Box, 2) && !m_Box->IsColliding(m_Wall, 2)) {
            m_Hero->SetState(HeroState::KICK);
            m_Box->MoveDown(moveStep);
            m_Hero->GetKickAnimation()->SetCurrentFrame(0);
            m_Hero->GetKickAnimation()->Play();
        }
    }
    m_Down = Util::Input::IsKeyDown(Util::Keycode::S);

    if (m_Left) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (!m_Hero->IsColliding(m_Wall, 3) && !m_Hero->IsColliding(m_Box, 3)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveLeft(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
        else if (m_Hero->IsColliding(m_Box, 3) && !m_Box->IsColliding(m_Wall, 3)) {
            m_Hero->SetState(HeroState::KICK);
            m_Box->MoveLeft(moveStep);
            m_Hero->GetKickAnimation()->SetCurrentFrame(0);
            m_Hero->GetKickAnimation()->Play();
        }
    }
    m_Left = Util::Input::IsKeyDown(Util::Keycode::A);

    if (m_Right) {
        m_Hero->SetCenter();
        m_Box->SetCenter();
        if (!m_Hero->IsColliding(m_Wall, 4) && !m_Hero->IsColliding(m_Box, 4)) {
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveRight(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
        else if (m_Hero->IsColliding(m_Box, 4) && !m_Box->IsColliding(m_Wall, 4)) {
            m_Hero->SetState(HeroState::KICK);
            m_Box->MoveRight(moveStep);
            m_Hero->GetKickAnimation()->SetCurrentFrame(0);
            m_Hero->GetKickAnimation()->Play();
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
