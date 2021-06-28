//
// Created by Igor Obradovic.
//
#include <entry/Memory.hpp>
#include <fstream>
#include <game/state/StateFactory.hpp>

namespace game
{

Memory::Memory(const char* applicationName)
    : mGameData{ std::make_unique<::common::GameData>(applicationName) }
    , mClock{}
{
    try
    {
        mGameData->machine().addState(StateFactory::getState(machine::StateType::INTRO, *mGameData));
    }
    catch (const std::out_of_range& except) // TODO: 2 stage initialization
    {
        throw except;
    }
}

int Memory::run()
{
    try
    {
        while (mGameData->window().isOpen())
        {
            auto dt = mClock.restart();
            mGameData->machine().processChanges();

            mGameData->machine().activeState()->handleInput();
            mGameData->machine().activeState()->update(dt.asSeconds());

            if (mGameData->machine().shouldStopApplication())
            {
                mGameData->window().close();
            }
            mGameData->machine().activeState()->draw();
        }
    }
    catch (const std::out_of_range& except)
    {
        throw except;
    }

    return 0;
}

}  // namespace game
