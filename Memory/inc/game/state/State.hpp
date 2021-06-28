//
// Created by Igor Obradovic.
//
#pragma once

#include <cinttypes>

namespace machine
{

enum class StateType : std::uint8_t
{
    INTRO = 0u,
    GAME,
    END,
};

class State
{
public:
    State()          = default;
    virtual ~State() = default;

    State(State const&) = delete;
    State& operator=(State const&) = delete;

    // rule of 5, and indicates that this shall not be temporary object!
    State(State const&&) = delete;
    State& operator=(State const&&) = delete;

    virtual void update(float const deltaTime) = 0;
    virtual void handleInput()                 = 0;
    virtual void draw()                        = 0;
};

}  // namespace machine
