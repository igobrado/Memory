//
// Created by Igor Obradovic.
//
#pragma once

#include <cinttypes>
#include <cmath>
#include <game/animations/SfinaeHelpers.hpp>
#include <utility>

enum class AnimationState : std::uint8_t
{
    kInProgress = 0u,
    kSleep
};

template <typename T, typename Derived>
class AnimationBase
{
public:
    using AnimatedObject    = T;
    using AnimatedObjectPtr = AnimatedObject*;

    AnimationBase(AnimatedObjectPtr animated, float duration)
        : m_Animated{ animated }
        , m_AnimationDuration{ duration }
        , m_ElapsedTime{ 0.0f }
        , m_HalfTimeAnimation{ duration / 2.0f }
        , m_AnimationState{ AnimationState::kSleep }
    {
    }

    void updateAnimation(float const deltaTime)
    {
        static_assert(
                traits::HasStopAnimation<Derived>::value,
                "Derived class must implement function with signature "
                "void stopAnimation()");
        static_assert(
                traits::HasInvalidateTransform<Derived>::value,
                "Derived class must implement function with signature "
                "void invalidateTransform()");

        if (!isOver())
        {
            m_ElapsedTime += deltaTime;
            auto& derived = static_cast<Derived&>(*this);
            if (m_ElapsedTime >= m_AnimationDuration)
            {
                derived.stopAnimation();
                return;
            }
            derived.invalidateTransform();
        }
    }

    bool isOver() const
    {
        return m_AnimationState == AnimationState::kSleep;
    }

    float duration() const
    {
        return m_AnimationDuration;
    }

protected:
    void setAnimationState(AnimationState const state)
    {
        m_AnimationState = state;
    }

    double constexpr pi() const
    {
        return std::acos(-1);
    }

protected:
    AnimatedObjectPtr m_Animated;
    float             m_AnimationDuration;
    float             m_ElapsedTime;
    float             m_HalfTimeAnimation;

private:
    AnimationState m_AnimationState;
};