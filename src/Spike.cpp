#include "Spike.hpp"
#include "Util/Logger.hpp"
#include <string>

Spike::Spike(bool isOn, bool isStatic, glm::vec2 position): Tile(GA_RESOURCE_DIR"/Image/Spike/Sprite.png")
{

    std::vector<std::string> onImages;
    std::vector<std::string> offImages;

    for (int i = 0; i < 5; ++i) {
        offImages.emplace_back(GA_RESOURCE_DIR"/Image/Spike/spike" + std::to_string(i + 1) + ".png");
    }

    for (int i = 5; i < 8; ++i) {
        onImages.emplace_back(GA_RESOURCE_DIR"/Image/Spike/spike" + std::to_string(i + 1) + ".png");
    }

    onAnimation = std::make_shared<AnimatedCharacter>(onImages, false, 83, false);

    offAnimation = std::make_shared<AnimatedCharacter>(offImages, false, 83, false);

    onAnimation->SetZIndex(3);
    offAnimation->SetZIndex(3);
    this->SetPosition(position);
    onAnimation->SetPosition(position);
    offAnimation->SetPosition(position);

    isSpikeStatic = isStatic;
    
    if (isStatic){
        offAnimation->SetCurrentFrame(2);
        onAnimation->SetVisible(false);
        offAnimation->SetVisible(true);
        return;
    }

    isSpikeOn = isOn;
    
    if (isOn){
        onAnimation->SetCurrentFrame(2);
        onAnimation->SetVisible(true);
        offAnimation->SetVisible(false);
    }
    else{
        offAnimation->SetCurrentFrame(4);
        onAnimation->SetVisible(false);
        offAnimation->SetVisible(true);
    }
}

bool Spike::Collides(const std::shared_ptr<Hero>& other) const
{
    if(GetCenter() == other->GetCenter()){
        if (isSpikeOn || isSpikeStatic){
            Util::SFX m_SoundEffects(GA_RESOURCE_DIR"/Audio/spikes_damage_01.wav");
            m_SoundEffects.SetVolume(50);
            m_SoundEffects.Play();
            
            other->SetLevelStep(other->GetStep() - 1);
        }
        return true;
    }
    return false;
}

void Spike::PlayAnimation()
{
    if (isSpikeStatic){
        return;
    }
    isSpikeOn = !isSpikeOn;
    onAnimation->SetVisible(isSpikeOn);
    offAnimation->SetVisible(!isSpikeOn);

    if (isSpikeOn){
        onAnimation->SetCurrentFrame(0);
        onAnimation->Play();
    }
    else{
        offAnimation->SetCurrentFrame(0);
        offAnimation->Play();
    }
    
    
}