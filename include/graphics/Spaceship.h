#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <GlobalResources.h>
#include <graphics/CoordinateTransformation.h>
#include <simulation/ShipCollisionModel.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace ExomoMarsLander
{
    /**
     * Graphical representation of the space ship
     * */
    class Spaceship
    {
        public:
            Spaceship();

            /** Initialisiere das Raumschiff */
            void initialize();

            /** Setze Position des Raumschiffs */
            void setPosition(double x, double y);

            /** Setze aktuelle Drehung des Raumschiffs */
            void setRotation(double r);

            /** Aktiviert die Darstellung der Triebwerke */
            void enableFlame(bool enable);

            /** Zeichne das Raumschiff auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);

        private:
            /* Referenz auf den Resourcen Manager */
            const GlobalResources& globalResources;

            sf::CircleShape flame;
            sf::Sprite bodySprite;
            sf::Sound engineSound;

            bool flameOn;

            float posX;
            float posY;
            float rot;
    };
}

#endif //SPACESHIP_H