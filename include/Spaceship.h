#ifndef SPACESHIP_H
#define SPACESHIP_H

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

            /** Setze Position des Raumschiffs */
            void setPosition(double x, double y);

            /** Setze aktuelle Drehung des Raumschiffs */
            void setRotation(double r);

            /** Aktiviert die Darstellung der Triebwerke */
            void enableFlame(bool enable);

            /* Zeichne das Raumschiff auf das Zeichenfenster */
            void drawTo(sf::RenderTarget& target);
            
        private:
            sf::CircleShape nose;
            sf::CircleShape body;
            sf::CircleShape flame;
            bool flameOn;

            float posX;
            float posY;
            float rot;
    };
}

#endif //SPACESHIP_H