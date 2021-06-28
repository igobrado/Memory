//
// Created by Igor Obradovic.
//
#include <common/Math.hpp>
#include <game/animations/TableRotationAnimation.hpp>

TableRotationAnimation::TableRotationAnimation(sf::View* animated, float const duration)
    : AnimationBase<sf::View, TableRotationAnimation>{ animated, duration }
    , m_RotationAngle{ 0.0f }
    , m_CurrentAngle{ 0.0f }
{
}

void TableRotationAnimation::setRotationAngle(float const& angle)
{
    m_RotationAngle = angle;
}

void TableRotationAnimation::startAnimation()
{
    setAnimationState(AnimationState::kInProgress);
}

void TableRotationAnimation::stopAnimation()
{
    setAnimationState(AnimationState::kSleep);
    m_CurrentAngle += m_RotationAngle;

    m_RotationAngle = 0.f;
    m_ElapsedTime   = 0.f;
}

void TableRotationAnimation::invalidateTransform()
{
    auto rotation = m_RotationAngle * (float)std::sin(m_ElapsedTime / m_AnimationDuration * half(pi())) + m_CurrentAngle;

    // negative for clockwise rotation
    m_Animated->setRotation(-rotation);
}

void TableRotationAnimation::setRotationDuration(float const duration)
{
    m_AnimationDuration = duration;
}
