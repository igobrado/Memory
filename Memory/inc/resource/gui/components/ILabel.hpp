//
// Created by Igor Obradovic
//
#pragma once
#include <SFML/Graphics.hpp>
#include <resource/gui/components/IGuiComponent.hpp>
#include <string>

class ILabel : public IGuiComponent
{
public:
    virtual ~ILabel(){};

    virtual void               changeText(std::string const& textToSet) = 0;

    ComponentType type() override final
    {
        return ComponentType::kLabel;
    };

private:
    void handleInput(sf::Event&) override{};  // Change of the virtual function visibility to stand that label can't be
                                              // responsible for input, only for printing!
};