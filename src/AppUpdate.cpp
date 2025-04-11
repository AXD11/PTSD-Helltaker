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
        LOG_DEBUG(enemyPtr[12]->GetCenter());
        LOG_DEBUG(m_Hero->GetCenter());
        if (m_Hero->CanMove(1, testPtr) && !m_Hero->MeetEnemy(1, enemyPtr, testPtr)) {
            LOG_DEBUG("Change to Move");
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
        LOG_DEBUG(enemyPtr[12]->GetCenter());
        LOG_DEBUG(m_Hero->GetCenter());
        if (m_Hero->CanMove(2, testPtr) && !m_Hero->MeetEnemy(2, enemyPtr, testPtr)) {
            LOG_DEBUG("Change to Move");
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
        LOG_DEBUG(enemyPtr[12]->GetCenter());
        LOG_DEBUG(m_Hero->GetCenter());
        if (m_Hero->CanMove(3, testPtr) && !m_Hero->MeetEnemy(3, enemyPtr, testPtr)) {
            LOG_DEBUG("Change to Move");
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
        LOG_DEBUG(enemyPtr[12]->GetCenter());
        LOG_DEBUG(m_Hero->GetCenter());
        if (m_Hero->CanMove(4, testPtr) && !m_Hero->MeetEnemy(4, enemyPtr, testPtr)) {
            LOG_DEBUG("Change to Move");
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->MoveRight(moveStep);
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->GetMoveAnimation()->Play();
        }
    }
    m_Right = Util::Input::IsKeyDown(Util::Keycode::D);

    if ((m_Hero->GetMoveAnimation()->IfAnimationEnds() || 
         m_Hero->GetKickAnimation()->IfAnimationEnds())&&
         m_Hero->GetCurrentState() != HeroState::STANDBY) 
    {
        m_Hero->GetStandbyAnimation()->SetPosition(m_Hero->GetPosition());
        m_Hero->SetState(HeroState::STANDBY);
        LOG_DEBUG("Hero change to Standby");
        // LOG_DEBUG(m_Hero->GetStandbyAnimation()->IsLooping());
    }

    for (auto skelton : enemyPtr) {
        if (skelton == nullptr) continue;
        if (skelton->GetCurrentState() == EnemyState::BEKICKED && skelton->GetBeKickedAnimation()->IfAnimationEnds() && skelton->GetCurrentState() != EnemyState::DEAD) {
            skelton->GetBeKickedAnimation()->SetPosition(skelton->GetPosition());
            // skelton->GetBeKickedAnimation()->Play();
            skelton->SetState(EnemyState::STANDBY);
            LOG_DEBUG("Skelton change to Standby");
        }
    }
    

    m_Root.Update();
}
