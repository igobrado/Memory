//
// Created by Igor Obradovic.
//
#pragma once

#include <common/GameData.hpp>
#include <game/state/State.hpp>
#include <game/state/impl/EndgameState.hpp>
#include <game/state/impl/GameState.hpp>
#include <game/state/impl/IntroState.hpp>
#include <memory>

class StateFactory
{
public:
    static std::unique_ptr<machine::State> getState(machine::StateType const stateType, common::GameData& data)
    {
        try
        {
            switch (stateType)
            {
                case machine::StateType::INTRO:
                    return std::make_unique<machine::IntroState>(data);
                case machine::StateType::GAME:
                    return std::make_unique<machine::GameState>(data);
                case machine::StateType::END:
                    return std::make_unique<machine::EndgameState>(data);
                default:
                    return nullptr;
            }
        }
        catch (const std::exception& except)
        {
            throw except;
        }
    }
};
