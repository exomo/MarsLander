#include <GlobalResources.h>

#include <iostream>
#include <sstream>

using namespace ExomoMarsLander;

void GlobalResources::LoadResources()
{
    /* Schriftart laden, die zum Anzeigen von Texten verwendet wird */
    if(!textFont.loadFromFile("./resources/Amaranth-Italic.otf"))
    {
        throw resource_exception("./resources/Amaranth-Italic.otf");
    }

    /* Grafiken laden */
    if(!spaceshipTexture.loadFromFile("./resources/spaceship.png"))
    {
        throw resource_exception("./resources/spaceship.png");
    }
    spaceshipTexture.setSmooth(true);
    if(!flameTexture.loadFromFile("./resources/flame.png"))
    {
        throw resource_exception("./resources/flame.png");
    }
    flameTexture.setSmooth(true);
    if(!surfaceTexture.loadFromFile("./resources/mars_texture.png"))
    {
        throw resource_exception("./resources/mars_texture.png");
    }

    /* Sound laden */
    if(!engineSound.loadFromFile("./resources/engine_takeoff.wav"))
    {
        throw resource_exception("./resources/engine_takeoff.wav");
    }

}

const sf::Font& GlobalResources::GetFont() const
{
    return textFont;
}


const sf::Texture& GlobalResources::GetSpaceship() const
{
    return spaceshipTexture;
}

const sf::SoundBuffer& GlobalResources::GetEngineSound() const
{
    return engineSound;
}

const sf::Texture& GlobalResources::GetSurface() const
{
    return surfaceTexture;
}

const sf::Texture& GlobalResources::GetFlame() const
{
    return flameTexture;
}