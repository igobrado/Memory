//
// Created by Igor Obradovic
//
#pragma once

#include <resource/gui/components/IClickable.hpp>
#include <resource/gui/components/IGuiComponent.hpp>

class IButton
    : public IGuiComponent
    , public IClickable
{
public:
    virtual ~IButton(){};
    virtual void operator+=(OnClickCheckCallback callback) = 0;

    ComponentType type() override
    {
        return ComponentType::kButton;
    };
};