//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <cinttypes>

static std::uint8_t constexpr sBorderQuantity = 4;
static float constexpr sHudPieceHeight        = 50.f;

using PlayerPositions = std::array<sf::Vector2f const, sBorderQuantity>;
using Rotations       = std::array<float const, sBorderQuantity>;
using Hud             = std::array<sf::RectangleShape, sBorderQuantity>;
