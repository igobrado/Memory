//
// Created by Igor Obradovic.
//
#pragma once

#include <memory>
#include <resource/gui/components/IGuiComponent.hpp>
#include <utility>

template <typename ValueType, typename... Args>
std::unique_ptr<ValueType> makeGuiComponent(Args&&... args)
{
    static_assert(
            std::is_constructible<ValueType, Args...>::value || std::is_base_of<IGuiComponent, ValueType>::value,
            "Type is not constructable from given params!");

    return std::make_unique<ValueType>(std::forward<Args>(args)...);
}
