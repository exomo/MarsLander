#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include <graphics/Spaceship.h>

using namespace ExomoMarsLander;

Spaceship::Spaceship()
    : globalResources(GlobalResources::GetInstance())
    , flameOn(false)
{

    bodySprite.setTexture(globalResources.GetSpaceship(), true);
    bodySprite.setOrigin(bodySprite.getLocalBounds().width / 2, bodySprite.getLocalBounds().height / 2);

    engineSound.setBuffer(globalResources.GetEngineSound());
    engineSound.setLoop(true);


    flameSprite.setTexture(globalResources.GetFlame());
    flameSprite.setOrigin(16,0);
}


void Spaceship::setPosition(double x, double y)
{
    bodySprite.setPosition(x,y);
    flameSprite.setPosition(x, y);
}

void Spaceship::setRotation(double r)
{
    bodySprite.setRotation(r);
    flameSprite.setRotation(r);
}

void Spaceship::drawTo(sf::RenderTarget& target)
{
    if(flameOn) 
    {
        // durch eine zufällige Skalierung wird ein Flacker-Effekt der Flamme erzeugt
        std::uniform_real_distribution<float> scaleDist(0.9, 1.0);
        auto scale = scaleDist(mt);

        flameSprite.setScale(scale, scale);
        target.draw(flameSprite);
    }

    target.draw(bodySprite);
}

void Spaceship::enableFlame(bool enable)
{
    if(!flameOn && enable)
    {
        engineSound.play();
    }
    if(flameOn && !enable)
    {
        engineSound.stop();
    }
    flameOn = enable;
}

void Spaceship::initialize()
{

}
