#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <memory>
#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

#include <iostream>


class AnimatedCharacter : public Util::GameObject {

public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths, bool play, int interval, bool loop);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    [[nodiscard]] bool IfAnimationEnds() const;

    void SetCurrentFrame(std::size_t index) {
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        animation->SetCurrentFrame(index);
    }

    void Play(){
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        animation->Play();
    }

    void Inverse(){
        auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    
    }
};

#endif //ANIMATED_CHARACTER_HPP
