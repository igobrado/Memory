//
// Created by Igor Obradovic.
//
#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <game/animations/AnimationBase.hpp>

class ScreenSwapAnimation : public AnimationBase<sf::RectangleShape, ScreenSwapAnimation>
{
public:
    ScreenSwapAnimation(sf::RectangleShape* rect, float const duration);

    void startAnimation();
    void stopAnimation();
    void invalidateTransform();

private:
    sf::Color m_Color;
};