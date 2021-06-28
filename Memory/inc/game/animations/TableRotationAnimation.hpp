//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics/View.hpp>
#include <game/animations/AnimationBase.hpp>

class TableRotationAnimation : public AnimationBase<sf::View, TableRotationAnimation>
{
public:
    TableRotationAnimation(sf::View* viewAnimated, float const duration);

    void setRotationAngle(float const& angle);
    void startAnimation();
    void stopAnimation();
    void invalidateTransform();
    void setRotationDuration(float const duration);

private:
    float m_RotationAngle;
    float m_CurrentAngle;
};