//
// Created by Igor Obradovic.
//
#pragma once
#include <functional>
#include <game/animations/AnimationBase.hpp>

class Timeout
{
public:
    Timeout(std::function<void()>&& afterTimeoutEndsCallback, float timeoutDuration);
    Timeout(float timeoutDuration);

    void update(float const deltaTime);
    void reset(std::function<void()>&& afterTimeoutEndsCallback, float timeoutDuration);
    bool isBlocking() const;
protected:
    void setFireAndForget();

private:
    std::function<void()> m_AfterTimeoutEndsCallback;

    float m_TimeoutDuration;
    float m_ElapsedTime;
    bool  m_IsTimeoutOver;
};