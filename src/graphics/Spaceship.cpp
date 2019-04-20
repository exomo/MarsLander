#include <iostream>
#include <sstream>
#include <string>

#include <graphics/Spaceship.h>

using namespace ExomoMarsLander;

Spaceship::Spaceship()
    : nose(20, 3), body(20), flame(8,3), flameOn(false)
{
    nose.setOrigin(20,40);
    nose.setFillColor(sf::Color(100, 250, 50));
    nose.setOutlineColor(sf::Color(200, 150, 50));
    nose.setOutlineThickness(3);

    body.setOrigin(20,20);
    body.setFillColor(sf::Color(100, 250, 50));
    body.setOutlineColor(sf::Color(200, 150, 50));
    body.setOutlineThickness(3);

    flame.setFillColor(sf::Color(250, 250, 50));
    flame.setOrigin(8,36);
    flame.setRotation(180);
}


void Spaceship::setPosition(double x, double y)
{
    nose.setPosition(x,y);
    body.setPosition(x, y);
    flame.setPosition(x, y);
}

void Spaceship::setRotation(double r)
{
    nose.setRotation(r);
    flame.setRotation(r + 180);
}

void Spaceship::drawTo(sf::RenderTarget& target)
{
    target.draw(nose);
    target.draw(body);
    if(flameOn) target.draw(flame);
}

void Spaceship::enableFlame(bool enable)
{
    flameOn = enable;
}

void Spaceship::initialize()
{

}
