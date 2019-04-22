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
}

const sf::Font& GlobalResources::GetFont() const
{
    return textFont;
}


const sf::Texture& GlobalResources::GetSpaceship() const
{
    return spaceshipTexture;
}
