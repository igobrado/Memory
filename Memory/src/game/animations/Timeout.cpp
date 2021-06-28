//
// Created by Igor Obradovic.
//
#include <game/animations/Timeout.hpp>

Timeout::Timeout(std::function<void()>&& afterTimeoutEndsCallback, float timeoutDuration)
    : m_AfterTimeoutEndsCallback{ std::move(afterTimeoutEndsCallback) }
    , m_TimeoutDuration{ timeoutDuration }
    , m_ElapsedTime{ 0 }
    , m_IsTimeoutOver{ false }
{
}

Timeout::Timeout(float timeoutDuration)
    : m_AfterTimeoutEndsCallback{ nullptr }
    , m_TimeoutDuration{ timeoutDuration }
    , m_ElapsedTime{ 0 }
    , m_IsTimeoutOver{ true }
{
}

void Timeout::update(const float deltaTime)
{
    if (m_IsTimeoutOver || !m_AfterTimeoutEndsCallback)
    {
        return;
    }

    m_ElapsedTime += deltaTime;
    if (m_ElapsedTime >= m_TimeoutDuration)
    {
        setFireAndForget();
    }
}
void Timeout::setFireAndForget()
{
    m_IsTimeoutOver = true;
    m_AfterTimeoutEndsCallback();

    m_AfterTimeoutEndsCallback = nullptr;
    m_ElapsedTime              = 0;
}

void Timeout::reset(std::function<void()>&& afterTimeoutEndsCallback, float timeoutDuration)
{
    m_AfterTimeoutEndsCallback = std::move(afterTimeoutEndsCallback);
    m_TimeoutDuration          = timeoutDuration;
    m_IsTimeoutOver            = false;
    m_ElapsedTime              = 0;
}

bool Timeout::isBlocking() const
{
    return m_IsTimeoutOver;
}
