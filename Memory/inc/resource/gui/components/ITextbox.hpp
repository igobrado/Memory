//
// Created by Igor Obradovic
//
#pragma once

#include <resource/gui/components/IClickable.hpp>
#include <resource/gui/components/IGuiComponent.hpp>
#include <resource/gui/components/IWriteable.hpp>

class ITextbox
    : public IGuiComponent
    , public IClickable
    , public IWriteable
{
public:
    virtual ~ITextbox(){};
    ComponentType type() override final
    {
        return ComponentType::kTextbox;
    };
};