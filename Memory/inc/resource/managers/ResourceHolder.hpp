//
// Created by Igor Obradovic.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <resource/managers/Manager.hpp>

class ResourceHolder
{
public:
    ResourceHolder();

    sf::Texture& texture(std::string const& targetID);
    sf::Font&    font(std::string const& targetID);

    void play(std::string const& sound);
    void setRepeatPlaying(std::string const& sound);
private:
    FontManager    m_FontManager;
    TextureManager m_TextureManager;
    SoundManager   m_SoundManager;
};
