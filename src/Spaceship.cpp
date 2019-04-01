#include <iostream>
#include <sstream>
#include <string>

#include <Spaceship.h>

using namespace ExomoMarsLander;

Spaceship::Spaceship()
    : body(20), flame(8,3), flameOn(false)
{
        body.setOrigin(20,20);
        body.setFillColor(sf::Color(100, 250, 50));
        body.setOutlineColor(sf::Color(200, 150, 50));
        body.setOutlineThickness(3);

        flame.setFillColor(sf::Color(250, 250, 50));
        flame.setOrigin(8,8);
        flame.setRotation(3.14);
}


void Spaceship::setPosition(double x, double y)
{
    body.setPosition(x, y);
    flame.setPosition(x, y+28);
}

void Spaceship::drawTo(sf::RenderTarget& target)
{
    target.draw(body);
    if(flameOn) target.draw(flame);
}

void Spaceship::enableFlame(bool enable)
{
    flameOn = enable;
}