//
// Created by Igor Obradovic.
//
#pragma once
#include <functional>
#include <string>

using OnClickCheckCallback = std::function<void()>;
class IClickable
{
public:
    virtual ~IClickable(){};

protected:
    virtual void onClick() = 0;
};