#include "AnimatedCharacter.hpp"


AnimatedCharacter::AnimatedCharacter(const std::vector<std::string>& AnimationPaths, int interval, bool loop) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, interval, loop, 0);
}

bool AnimatedCharacter::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}
