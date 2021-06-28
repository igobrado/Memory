//
// Created by Igor Obradovic.
//
#pragma once
#include <resource/gui/components/IGuiComponent.hpp>
#include <unordered_map>

static ComponentType toComponentType(char const* componentType)
{
    static std::unordered_map<std::string, ComponentType> sComponentTypes{ { "Button", ComponentType::kButton },
                                                                           { "Label", ComponentType::kLabel },
                                                                           { "Textbox", ComponentType::kTextbox },
                                                                           { "Counter", ComponentType::kCounter } };

    return sComponentTypes[componentType];
}
