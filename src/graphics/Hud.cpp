#include <iostream>
#include <sstream>
#include <string>

#include <graphics/Hud.h>

using namespace ExomoMarsLander;

Hud::Hud()
    : globalResources(GlobalResources::GetInstance())
    , textFont(globalResources.GetFont())
{

}

void Hud::drawTo(sf::RenderTarget& target)
{
    fuelLevelShape.setSize(sf::Vector2f(fuelLevel, 24));

    std::wstringstream altitudeString;
    altitudeString << L"Höhe: " << (altitude / 1000) << "m";
    altitudeText.setString(altitudeString.str());

    target.draw(altitudeText);
    target.draw(fuelText);
    target.draw(fuelLevelShape);
    target.draw(fuelBorder);
}

void Hud::initialize()
{
    altitudeText.setFont(textFont);
    altitudeText.setCharacterSize(24);
    altitudeText.setFillColor(sf::Color::Blue);
    altitudeText.setPosition(15, 5);
    altitudeText.setOutlineColor(sf::Color::Green);
    altitudeText.setOutlineThickness(1);

    fuelText.setFont(textFont);
    fuelText.setCharacterSize(24);
    fuelText.setFillColor(sf::Color::Blue);
    fuelText.setPosition(15, 45);
    fuelText.setOutlineColor(sf::Color::Green);
    fuelText.setOutlineThickness(1);

    std::string t = u8"Treibstoff:";
    fuelText.setString(sf::String::fromUtf8(t.begin(), t.end()));

    t = u8"Höhe:";
    altitudeText.setString(sf::String::fromUtf8(t.begin(), t.end()));

    auto fuelBarLeft = fuelText.getGlobalBounds().left + fuelText.getGlobalBounds().width + 20;

    fuelBorder.setPosition(sf::Vector2f(fuelBarLeft, 49));
    fuelBorder.setSize(sf::Vector2f(100, 24));
    fuelBorder.setFillColor(sf::Color::Transparent);
    fuelBorder.setOutlineColor(sf::Color::Green);
    fuelBorder.setOutlineThickness(2);

    fuelLevelShape.setPosition(sf::Vector2f(fuelBarLeft, 49));
    fuelLevelShape.setSize(sf::Vector2f(50, 24));
    fuelLevelShape.setFillColor(sf::Color::Red);
}

void Hud::setAltitude(double altitude)
{
    this->altitude = altitude;
}

void Hud::setFuel(double fuel)
{
    this->fuelLevel = fuel;
}