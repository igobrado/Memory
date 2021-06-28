//
// Created by Igor Obradovic.
//
#include <game/state/StateMachine.hpp>

namespace machine
{

StateMachine::StateMachine()
    : m_IsReplacing{ true }
    , m_IsAdding{ true }
    , m_IsRemoving{ false }
    , m_ShouldStop{ false }
    , mStates{}
    , mNextState{ nullptr }
{
}

std::unique_ptr<State> const& StateMachine::activeState() const
{
    return mStates.top();
}

void StateMachine::addState(std::unique_ptr<State> newState, bool isReplacing)
{
    if (newState)
    {
        mNextState    = std::move(newState);
        m_IsAdding    = true;
        m_IsReplacing = isReplacing;
    }
}

void StateMachine::processChanges()
{
    if (m_IsRemoving && !mStates.empty())
    {
        mStates.pop();
        m_IsRemoving = false;
    }
    if (m_IsAdding)
    {
        if (!mStates.empty())
        {
            if (m_IsReplacing)
            {
                mStates.pop();
            }
        }

        mStates.push(std::move(mNextState));
        m_IsAdding = false;
    }
}

bool StateMachine::shouldStopApplication() const
{
    return m_ShouldStop;
}

}  // namespace machine
