//
// Created by Igor Obradovic.
//
#pragma once

#include <game/state/State.hpp>
#include <memory>
#include <stack>

namespace machine
{

class StateMachine
{
public:
    StateMachine();

    std::unique_ptr<State> const& activeState() const;

    void addState(std::unique_ptr<State> newState, bool isReplacing = true);
    void processChanges();
    bool shouldStopApplication() const;

private:
    bool m_IsReplacing;
    bool m_IsAdding;
    bool m_IsRemoving;
    bool m_ShouldStop;

    std::stack<std::unique_ptr<State>> mStates;
    std::unique_ptr<State>             mNextState;
};

}  // namespace machine
