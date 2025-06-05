#include "App.hpp"

#include "Hero.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include <glm/fwd.hpp>

void App::Update() {

    m_Up = Util::Input::IsKeyDown(Util::Keycode::W);
    m_Down = Util::Input::IsKeyDown(Util::Keycode::S);
    m_Left = Util::Input::IsKeyDown(Util::Keycode::A);
    m_Right = Util::Input::IsKeyDown(Util::Keycode::D);

    //ESC退出遊戲
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    //M跳到下一關
    if (Util::Input::IsKeyDown(Util::Keycode::M)){
        if (currentLevel < 30){
            currentLevel++;
            nextLevel = true;
            reset = true;
            m_Hero->SetState(HeroState::STANDBY);
        }
    }

    //N跳到上一關
    if (Util::Input::IsKeyDown(Util::Keycode::N)){
        if (currentLevel > 1) {
            currentLevel--;
            nextLevel = true;
            reset = true;
            m_Hero->SetState(HeroState::STANDBY);
        }
    }

    //R或reset刷新關卡
    if (Util::Input::IsKeyDown(Util::Keycode::R) || reset) {

        eyeCatch->SetCurrentFrame(0);
        eyeCatch->SetVisible(true);
        eyeCatch->Play();
        
        reset = false;
        
        m_Hero->SetState(HeroState::STANDBY);
        m_Hero->IsKeyGet(true, m_Key);
        
        m_MapLoader.ClearMap(floorPtr, testPtr, enemyPtr, m_Root, m_Devil, m_Key);
        if (nextLevel){
            m_MapLoader.loadMap(GA_RESOURCE_DIR"/Map/Map" + std::to_string(currentLevel) + ".json");
            testPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
            floorPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());
            enemyPtr.resize(m_MapLoader.getHeight()* m_MapLoader.getWidth());  
            init_position = glm::vec2(50 - 100 * m_MapLoader.getWidth()/2, -50 + 100 * m_MapLoader.getHeight()/2);
            levelText->SetText(currentLevel);
            nextLevel = false;
        } 
        m_MapLoader.SetMap(init_position, floorPtr, testPtr, enemyPtr, m_Root, m_Hero, m_Devil, m_Key);

        stepLock = m_Hero->GetStep();

        blackScreen->SetVisible(false);
    }

    //W向上移動
    if (m_Up && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(1, testPtr, m_Devil,  enemyPtr) && !m_Hero->MeetEnemy(1, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveUp(moveStep);
            m_Hero->IsKeyGet(reset, m_Key);
        }
    }

    //S向下移動
    if (m_Down && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(2, testPtr, m_Devil, enemyPtr) && !m_Hero->MeetEnemy(2, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveDown(moveStep);
            m_Hero->IsKeyGet(reset, m_Key);
        }
    }

    //A向左移動
    if (m_Left && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(3, testPtr, m_Devil, enemyPtr) && !m_Hero->MeetEnemy(3, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveLeft(moveStep);
            m_Hero->IsKeyGet(reset, m_Key);
        }
    }

    //D向右移動
    if (m_Right && m_Hero->GetStep() > 0) {
        if (m_Hero->CanMove(4, testPtr, m_Devil, enemyPtr) && !m_Hero->MeetEnemy(4, enemyPtr, testPtr)) {
            m_Hero->GetMoveAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::MOVE);
            m_Hero->GetMoveAnimation()->Play();
            m_Hero->MoveRight(moveStep);
            m_Hero->IsKeyGet(reset, m_Key);
        }
    }

    //m_Hero重置到STANDBY狀態
    if ((m_Hero->GetMoveAnimation()->IfAnimationEnds() || m_Hero->GetKickAnimation()->IfAnimationEnds()) &&
         m_Hero->GetCurrentState() != HeroState::WIN &&
         m_Hero->GetCurrentState() != HeroState::DEAD &&
         m_Hero->GetCurrentState() != HeroState::STANDBY) 
    {
        m_Hero->GetStandbyAnimation()->SetPosition(m_Hero->GetPosition());
        m_Hero->GetStandbyAnimation()->SetCurrentFrame(0);
        m_Hero->SetState(HeroState::STANDBY);
    }


    //敵人狀態由BEKICKED轉為STANDBY
    for (auto skelton : enemyPtr) {
        if (skelton == nullptr) continue;
        if (skelton->GetCurrentState() == EnemyState::BEKICKED && skelton->GetBeKickedAnimation()->IfAnimationEnds() && skelton->GetCurrentState() != EnemyState::DEAD) {
            skelton->GetBeKickedAnimation()->SetPosition(skelton->GetPosition());
            skelton->SetState(EnemyState::STANDBY);
        }
    }
    
    
    if (m_Devil != nullptr){
        //達到目標位置
        if (m_Hero->IsNearBy(m_Devil) && !reset) {
            reset = true;
            currentLevel++;
            nextLevel = true;
            
        }

        //m_Hero死亡
        if (m_Hero->GetStep() == 0 && m_Hero->GetCurrentState() != HeroState::DEAD && !m_Hero->IsNearBy(m_Devil)) {
            m_Hero->GetDeadAnimation()->SetPosition({m_Hero->GetPosition().x, m_Hero->GetPosition().y + 232});
            m_Hero->GetDeadAnimation()->SetCurrentFrame(0);
            m_Hero->SetState(HeroState::DEAD);
            m_Hero->GetDeadAnimation()->Play();
            blackScreen->SetVisible(true);
        }
    }

    //轉場動畫將Visible設為false
    if (eyeCatch->IfAnimationEnds()){
        eyeCatch->SetVisible(false);
    }
    
    //m_Hero死亡動畫結束進行重置
    if (m_Hero->GetDeadAnimation()->IfAnimationEnds() && m_Hero->GetCurrentState() == HeroState::DEAD && !reset) {
        reset = true;
    }

    //動態尖刺動畫
    if ((m_Up || m_Right || m_Left || m_Down) && stepLock != m_Hero->GetStep()){
        for (auto tile: testPtr) {
            if (tile == nullptr) continue;
            if (auto spike = std::dynamic_pointer_cast<Spike>(tile)) {
                spike->PlayAnimation();
                spike->Collides(m_Hero);
            }
        }
        stepLock = m_Hero->GetStep();   //用於確認是否有移動或Kick
    }


    m_Root.Update();
}
