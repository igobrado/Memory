//
// Created by Igor Obradovic.
//
#include <resource/managers/ResourceHolder.hpp>

ResourceHolder::ResourceHolder()
    : m_FontManager{ "../resource/xml/Font.xml" }
    , m_TextureManager{ "../resource/xml/Textures.xml" }
    , m_SoundManager{ "../resource/xml/Sound.xml" }
{
}

sf::Texture& ResourceHolder::texture(const std::string& targetID)
{
    return m_TextureManager.getProperty(targetID);
}

sf::Font& ResourceHolder::font(const std::string& targetID)
{
    return m_FontManager.getProperty(targetID);
}

void ResourceHolder::play(const std::string& sound)
{
    m_SoundManager.play(sound);
}

void ResourceHolder::setRepeatPlaying(std::string const& sound)
{
    m_SoundManager.setRepeating(sound);
}
