//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <functional>
#include <game/animations/AnimationBase.hpp>

class CardFlipAnimation : public AnimationBase<sf::Sprite, CardFlipAnimation>
{
public:
    CardFlipAnimation(
            sf::Sprite*        sprite,  //
            float              duration,
            const sf::Texture* backTexture,
            const sf::Texture* frontTexture);

    void startAnimation();
    void stopAnimation();
    void invalidateTransform();

protected:
    void changeTexture();

private:
    bool               m_IsTransitionOver;
    float const        m_StartingScale;
    sf::Texture const* m_BackTexture;
    sf::Texture const* m_FrontTexture;
};