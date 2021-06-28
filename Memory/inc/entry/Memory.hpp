//
// Created by Igor Obradovic.
//
#pragma once

#include <common/GameData.hpp>
#include <memory>

namespace game
{

class Memory
{
public:
    explicit Memory(const char* applicationName);
    int run();

private:
    std::unique_ptr<::common::GameData> mGameData;
    sf::Clock                           mClock;
};

}  // namespace game
