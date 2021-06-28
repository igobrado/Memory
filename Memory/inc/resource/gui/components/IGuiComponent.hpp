//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics.hpp>

enum class ComponentType : std::uint8_t
{
    kButton = 0u,
    kTextbox,
    kLabel,
    kCounter
};

class IGuiComponent : public sf::Drawable
{
public:
    virtual ~IGuiComponent(){};
    virtual void               update(float const deltaTime){};
    virtual void               handleInput(sf::Event& event) = 0;
    virtual std::string        text() const                  = 0;
    virtual std::string const& name() const                  = 0;
    virtual ComponentType      type()                        = 0;
};
