#include "App.hpp"

#include "Hero.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <iostream>

void App::Update() {

    m_Up = Util::Input::IsKeyDown(Util::Keycode::W);
    m_Down = Util::Input::IsKeyDown(Util::Keycode::S);
    m_Left = Util::Input::IsKeyDown(Util::Keycode::A);
    m_Right = Util::Input::IsKeyDown(Util::Keycode::D);

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::R) || reset) {
        reset = false;

        m_Hero->SetState(HeroState::STANDBY);

        m_MapLoader.ClearMap(floorPtr, testPtr, enemyPtr, m_Root, m_Devil);
        if (nextLevel){
            m_MapLoader.loadMap(GA_RESOURCE_DIR"/Map/Map" + std::to_string(currentLevel) + ".json");
            testPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
            floorPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
            enemyPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());  
            init_position = glm::vec2(50 - 100 * m_MapLoader.getWidth()/2, -50 + 100 * m_MapLoader.getHeight()/2);
            nextLevel = false;
        } 
        m_MapLoader.SetMap(init_position, floorPtr, testPtr, enemyPtr, m_Root, m_Hero, m_Devil);

        stepLock = m_Hero->GetStep();

        blackScreen->SetVisible(false);
    }

    if (m_Up && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(1, testPtr) && !m_Hero->MeetEnemy(1, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveUp(moveStep);
        }
    }

    if (m_Down && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(2, testPtr) && !m_Hero->MeetEnemy(2, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveDown(moveStep);

        }
    }

    if (m_Left && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(3, testPtr) && !m_Hero->MeetEnemy(3, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveLeft(moveStep);

        }
    }

    if (m_Right && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(4, testPtr) && !m_Hero->MeetEnemy(4, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveRight(moveStep);
        }
    }

    if ((m_Hero->GetMoveAnimation()->IfAnimationEnds() || m_Hero->GetKickAnimation()->IfAnimationEnds()) &&
         m_Hero->GetCurrentState() != HeroState::WIN &&
         m_Hero->GetCurrentState() != HeroState::DEAD &&
         m_Hero->GetCurrentState() != HeroState::STANDBY) 
    {
        m_Hero->GetStandbyAnimation()->SetPosition(m_Hero->GetPosition());
        m_Hero->GetStandbyAnimation()->SetCurrentFrame(0);
        m_Hero->SetState(HeroState::STANDBY);
    }

    for (auto skelton : enemyPtr) {
        if (skelton == nullptr) continue;
        if (skelton->GetCurrentState() == EnemyState::BEKICKED && skelton->GetBeKickedAnimation()->IfAnimationEnds() && skelton->GetCurrentState() != EnemyState::DEAD) {
            skelton->GetBeKickedAnimation()->SetPosition(skelton->GetPosition());
            skelton->SetState(EnemyState::STANDBY);
        }
    }
    
    if (m_Devil != nullptr){
        if (m_Devil->IsNearBy(m_Hero) && !reset) {
            reset = true;
            currentLevel++;
            nextLevel = true;
            eyeCatch->SetCurrentFrame(0);
            eyeCatch->SetVisible(true);
            eyeCatch->Play();
        }

        if (m_Hero->GetStep() == 0 && m_Hero->GetCurrentState() != HeroState::DEAD && !m_Devil->IsNearBy(m_Hero)) {
            m_Hero->GetDeadAnimation()->SetPosition({m_Hero->GetPosition().x, m_Hero->GetPosition().y + 232});
            m_Hero->GetDeadAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::DEAD);
            m_Hero->GetDeadAnimation()->Play();
            blackScreen->SetVisible(true);
        }
    }

    if (eyeCatch->IfAnimationEnds()){
        eyeCatch->SetVisible(false);
    }
    
    if (m_Hero->GetDeadAnimation()->IfAnimationEnds() && m_Hero->GetCurrentState() == HeroState::DEAD && !reset) {
        reset = true;
    }

    if ((m_Up || m_Right || m_Left || m_Down) && stepLock != m_Hero->GetStep()){
        for (auto tile: testPtr) {
            if (tile == nullptr) continue;
            if (auto spike = std::dynamic_pointer_cast<Spike>(tile)) {
                spike->PlayAnimation();
                spike->Collides(m_Hero);
            }
        }
        stepLock = m_Hero->GetStep();
        // spikeChange = true;
    }


    m_Root.Update();
}
