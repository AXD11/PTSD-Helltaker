#ifndef SPIKE_HPP
#define SPIKE_HPP


#include "Tile.hpp"
#include "AnimatedCharacter.hpp"
#include "Hero.hpp"
#include <memory>

#include "Util/SFX.hpp"


class Spike : public Tile {
public:
    Spike(bool isOn, bool isStaic, glm::vec2 position);

    void SetState(bool isOn) { isSpikeOn = isOn; }

    void PlayAnimation();

    bool Collides(const std::shared_ptr<Hero>& other) const;

    [[nodiscard]] std::shared_ptr<AnimatedCharacter> GetOnAnimation() const { return onAnimation; }

    [[nodiscard]] std::shared_ptr<AnimatedCharacter> GetOffAnimation() const { return offAnimation; }

    [[nodiscard]] bool SpikeIsOn() { return isSpikeOn; }

private:
    std::shared_ptr<AnimatedCharacter> onAnimation;
    std::shared_ptr<AnimatedCharacter> offAnimation;
    bool isSpikeOn;
    bool isSpikeStatic;
    
};

#endif
