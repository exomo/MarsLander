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
}

const sf::Font& GlobalResources::GetFont() const
{
    return textFont;
}

