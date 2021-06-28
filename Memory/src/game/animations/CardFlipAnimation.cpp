//
// Created by Igor Obradovic.
//
#include <common/Math.hpp>
#include <game/animations/CardFlipAnimation.hpp>

CardFlipAnimation::CardFlipAnimation(
        sf::Sprite*        sprite,
        float              duration,
        const sf::Texture* backTexture,
        const sf::Texture* frontTexture)
    : AnimationBase<sf::Sprite, CardFlipAnimation>{ sprite, duration }
    , m_StartingScale{ sprite->getScale().x }
    , m_IsTransitionOver{ false }
    , m_BackTexture{ backTexture }
    , m_FrontTexture{ frontTexture }
{
}

void CardFlipAnimation::startAnimation()
{
    setAnimationState(AnimationState::kInProgress);
}

void CardFlipAnimation::stopAnimation()
{
    setAnimationState(AnimationState::kSleep);
    m_ElapsedTime      = 0;
    m_IsTransitionOver = false;
}

void CardFlipAnimation::invalidateTransform()
{
    if ((m_ElapsedTime >= m_HalfTimeAnimation) && (!m_IsTransitionOver))
    {
        changeTexture();
        m_IsTransitionOver = true;
    }

    float scale = 0;
    if (m_ElapsedTime <= m_HalfTimeAnimation)
    {
        scale = m_StartingScale - (m_ElapsedTime / m_HalfTimeAnimation);
    }
    else
    {
        scale = (m_ElapsedTime - m_HalfTimeAnimation) / m_HalfTimeAnimation;
    }

    m_Animated->setScale({ scale, 1. });
}

void CardFlipAnimation::changeTexture()
{
    if (m_Animated->getTexture() == m_BackTexture)
    {
        m_Animated->setTexture(*m_FrontTexture);
        return;
    }

    if (m_Animated->getTexture() == m_FrontTexture)
    {
        m_Animated->setTexture(*m_BackTexture);
        return;
    }
}
