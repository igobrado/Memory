//
// Created by Igor Obradovic
//
#pragma once
#include <SFML/Graphics.hpp>

class IWriteable
{
public:
    virtual ~IWriteable(){};

protected:
    virtual void checkTextChanged(sf::Uint64 const unicode) = 0;
};