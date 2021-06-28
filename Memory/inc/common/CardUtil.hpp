//
// Created by Igor Obradovic.
//
#pragma once

#include <cstdint>
#include <string>

static const char* const cardNames[] = { "Jack", "Queen", "King", "Ace" };

enum class CardType : std::uint8_t
{
    kJack = 0u,
    kQueen,
    kKing,
    kAce,
    kSize
};

enum class RevealStatus : std::uint8_t
{
    kRevealed = 0u,
    kNotRevealed
};

static std::string cardTypeToString(CardType type)
{
    static_assert(
            sizeof(cardNames) / sizeof(cardNames[0]) == static_cast<std::uint8_t>(CardType::kSize),
            "Not enough card names. If you update card type enum, update card names!");

    return cardNames[static_cast<std::uint8_t>(type)];
}
