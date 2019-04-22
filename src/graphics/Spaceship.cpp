#include <iostream>
#include <sstream>
#include <string>

#include <graphics/Spaceship.h>

using namespace ExomoMarsLander;

Spaceship::Spaceship()
    : globalResources(GlobalResources::GetInstance()) 
    , flame(8,3), flameOn(false)
{

    bodySprite.setTexture(globalResources.GetSpaceship(), true);
    bodySprite.setOrigin(bodySprite.getLocalBounds().width / 2, bodySprite.getLocalBounds().height / 2);

    flame.setFillColor(sf::Color(250, 250, 50));
    flame.setOrigin(8,36);
    flame.setRotation(180);
}


void Spaceship::setPosition(double x, double y)
{
    bodySprite.setPosition(x,y);
    flame.setPosition(x, y);
}

void Spaceship::setRotation(double r)
{
    bodySprite.setRotation(r);
    flame.setRotation(r + 180);
}

void Spaceship::drawTo(sf::RenderTarget& target)
{
    target.draw(bodySprite);
    if(flameOn) target.draw(flame);
}

void Spaceship::enableFlame(bool enable)
{
    flameOn = enable;
}

void Spaceship::initialize()
{

}
