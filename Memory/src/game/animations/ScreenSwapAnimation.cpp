//
// Created by Igor Obradovic.
//
#include <game/animations/ScreenSwapAnimation.hpp>

ScreenSwapAnimation::ScreenSwapAnimation(sf::RectangleShape* rect, const float duration)
    : AnimationBase<sf::RectangleShape, ScreenSwapAnimation>{ rect, duration }
    , m_Color{ 255, 255, 255, 0 }
{
    m_Animated->setFillColor(m_Color);
}

void ScreenSwapAnimation::startAnimation()
{
    setAnimationState(AnimationState::kInProgress);
}

void ScreenSwapAnimation::stopAnimation()
{
    setAnimationState(AnimationState::kSleep);
    m_ElapsedTime = 0;
}

void ScreenSwapAnimation::invalidateTransform()
{
    if ((m_Color.a + static_cast<sf::Uint8>(m_ElapsedTime)) <= 255)  // if alfa goes through 255 then color release's to transparent
    {
        m_Color.a += static_cast<sf::Uint8>(m_ElapsedTime);
        m_Animated->setFillColor(m_Color);
    }
}
