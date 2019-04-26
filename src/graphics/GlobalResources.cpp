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
    if(!spaceTexture.loadFromFile("./resources/space.png"))
    {
        throw resource_exception("./resources/space.png");
    }
    if(!spaceshipTexture.loadFromFile("./resources/spaceship.png"))
    {
        throw resource_exception("./resources/spaceship.png");
    }
    spaceshipTexture.setSmooth(true);
    if(!planetTexture.loadFromFile("./resources/planet.png"))
    {
        throw resource_exception("./resources/planet.png");
    }
    planetTexture.setSmooth(true);
    if(!surfaceTexture.loadFromFile("./resources/surface.jpg"))
    {
        throw resource_exception("./resources/surface.jpg");
    }
    surfaceTexture.setSmooth(true);

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

const sf::Texture& GlobalResources::GetSpace() const
{
    return spaceTexture;
}

const sf::Texture& GlobalResources::GetPlanet() const
{
    return planetTexture;
}

const sf::Texture& GlobalResources::GetSurface() const
{
    return surfaceTexture;
}

const sf::SoundBuffer& GlobalResources::GetEngineSound() const
{
    return engineSound;
}